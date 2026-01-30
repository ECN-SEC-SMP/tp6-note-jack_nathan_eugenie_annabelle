/**
 * @file testBot.cpp
 * @brief Tests unitaires pour la classe Bot
 * @version 0.1
 * @date 2026-01-30
 *
 * @copyright (c) 2026
 *
 * Nécessite board.h avec l'interface Board (isEmpty, canPlacePion, addPion,
 * wouldWin, wouldOpponentWin, getOpponentColors).
 */

#include "tests.hpp"
#include "Bot.hpp"
#include "board.h"
#include "Color.hpp"
#include "Size.hpp"
#include "Pion.hpp"

#include <cassert>
#include <iostream>
#include <vector>

/* --------------------------------------------------------------------------- */
/* MockBoard : plateau factice pour tester le Bot sans dépendre du vrai Board  */
/* --------------------------------------------------------------------------- */

/**
 * Grille 3x3 : chaque case peut contenir un pion (ou être vide).
 * Implémentation minimale pour les tests (pas de règle de victoire réelle).
 */
class MockBoard : public Board
{
public:
    MockBoard()
    {
        for (int i = 0; i < NB_ROW; ++i)
            for (int j = 0; j < NB_COL; ++j)
                grid[i][j] = nullptr;
    }

    ~MockBoard() override
    {
        for (int i = 0; i < NB_ROW; ++i)
            for (int j = 0; j < NB_COL; ++j)
                delete grid[i][j];
    }

    bool isEmpty(int x, int y) const override
    {
        if (x < 0 || x >= NB_ROW || y < 0 || y >= NB_COL) return true;
        return grid[x][y] == nullptr;
    }

    bool canPlacePion(int x, int y, SIZE s) const override
    {
        if (x < 0 || x >= NB_ROW || y < 0 || y >= NB_COL) return false;
        return grid[x][y] == nullptr;
    }

    void addPion(int x, int y, const Pion& p) override
    {
        if (x < 0 || x >= NB_ROW || y < 0 || y >= NB_COL) return;
        delete grid[x][y];
        grid[x][y] = new Pion(p);
    }

    bool wouldWin(int x, int y, COLOR c, SIZE s) const override
    {
        (void)x;
        (void)y;
        (void)c;
        (void)s;
        return false; /* pour les tests on peut forcer true sur une case précise */
    }

    bool wouldOpponentWin(int x, int y, COLOR opponentColor, SIZE s) const override
    {
        (void)x;
        (void)y;
        (void)opponentColor;
        (void)s;
        return false;
    }

    std::vector<COLOR> getOpponentColors(COLOR myColor) const override
    {
        std::vector<COLOR> out;
        if (myColor != RED)   out.push_back(RED);
        if (myColor != BLUE)  out.push_back(BLUE);
        if (myColor != GREEN) out.push_back(GREEN);
        if (myColor != YELLOW) out.push_back(YELLOW);
        return out;
    }

private:
    Pion* grid[NB_ROW][NB_COL];
};

/* --------------------------------------------------------------------------- */
/* Tests                                                                        */
/* --------------------------------------------------------------------------- */

/**
 * @brief Test des constructeurs du Bot (1 couleur et plusieurs couleurs).
 */
static void testBotConstructors(void)
{
    std::cout << "[testBot] Constructeurs..." << std::endl;

    Bot bot1("BotRouge", RED);
    assert(bot1.getName() == "BotRouge");
    assert(bot1.getColor().size() == 1);
    assert(bot1.getColor()[0] == RED);

    Bot bot2("BotDouble", std::vector<COLOR>{BLUE, GREEN});
    assert(bot2.getName() == "BotDouble");
    assert(bot2.getColor().size() == 2);
    assert(bot2.getColor()[0] == BLUE && bot2.getColor()[1] == GREEN);

    std::cout << "[testBot] Constructeurs OK." << std::endl;
}

/**
 * @brief Test de getPossibleMoves : le bot doit retourner des coups sur un plateau vide.
 */
static void testBotGetPossibleMoves(void)
{
    std::cout << "[testBot] getPossibleMoves..." << std::endl;

    Bot bot("BotTest", RED);
    MockBoard board;

    std::vector<Move> moves = bot.getPossibleMoves(&board);
    /* Plateau vide 3x3, 3 tailles -> au plus 3*3*3 = 27 coups possibles (et le bot a des pions). */
    assert(!moves.empty());
    for (const Move& m : moves) {
        assert(m.x >= 0 && m.x < Board::NB_ROW);
        assert(m.y >= 0 && m.y < Board::NB_COL);
        assert(m.size >= SMALL && m.size <= LARGE);
    }

    std::cout << "[testBot] getPossibleMoves OK (" << moves.size() << " coups)." << std::endl;
}

/**
 * @brief Test de playTurn : le bot doit jouer un coup (curseur mis à jour, ENDPLAY).
 */
static void testBotPlayTurn(void)
{
    std::cout << "[testBot] playTurn..." << std::endl;

    Bot bot("BotTest", BLUE);
    MockBoard board;
    cursor_t cursor = {-1, -1};

    playerAction_t action = bot.playTurn(&board, &cursor);
    assert(action == ENDPLAY);
    assert(cursor.x >= 0 && cursor.x < Board::NB_ROW);
    assert(cursor.y >= 0 && cursor.y < Board::NB_COL);
    assert(!board.isEmpty(cursor.x, cursor.y));

    std::cout << "[testBot] playTurn OK (joué en " << cursor.x << "," << cursor.y << ")." << std::endl;
}

/**
 * @brief Test de nextMove : previsionsCoups est rempli (via un second appel ou en vérifiant le comportement).
 * On vérifie que nextMove ne plante pas et qu’après un getPossibleMoves on a des coups cohérents.
 */
static void testBotNextMove(void)
{
    std::cout << "[testBot] nextMove..." << std::endl;

    Bot bot("BotTest", GREEN);
    MockBoard board;

    bot.nextMove(&board);
    /* On ne peut pas accéder à previsionsCoups (privé), donc on vérifie juste que nextMove s’exécute. */
    std::vector<Move> moves = bot.getPossibleMoves(&board);
    assert(!moves.empty());

    std::cout << "[testBot] nextMove OK." << std::endl;
}

/**
 * @brief Test avec board == nullptr : le bot ne doit pas planter.
 */
static void testBotNullBoard(void)
{
    std::cout << "[testBot] Null board..." << std::endl;

    Bot bot("BotTest", RED);
    std::vector<Move> moves = bot.getPossibleMoves(nullptr);
    assert(moves.empty());

    cursor_t cursor = {0, 0};
    playerAction_t action = bot.playTurn(nullptr, &cursor);
    assert(action == PION_SEL_DISABLE);

    bot.nextMove(nullptr);

    std::cout << "[testBot] Null board OK." << std::endl;
}

/**
 * @brief Point d’entrée des tests Bot (à appeler depuis main ou tests.hpp).
 */
void testBot(void)
{
    std::cout << "\n========== Tests Bot ==========" << std::endl;
    testBotConstructors();
    testBotGetPossibleMoves();
    testBotPlayTurn();
    testBotNextMove();
    testBotNullBoard();
    std::cout << "========== Tests Bot OK ==========\n" << std::endl;
}
