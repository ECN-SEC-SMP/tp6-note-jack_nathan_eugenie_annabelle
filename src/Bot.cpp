#include "Bot.hpp"
#include <algorithm>
#include <random>
#include <chrono>

Bot::Bot(const std::string& name, COLOR color) : Player(name, {color}) {}

Bot::Bot(const std::string& name, std::vector<COLOR> assignedColor) : Player(name, assignedColor) {}

Bot::~Bot() {}

/**
 * @brief Construit la liste des coups possibles : pour chaque case (x,y) et
 * chaque taille de pion, on ajoute le coup si le bot possède encore un pion
 * de cette taille et si le plateau accepte ce placement.
 */
std::vector<Move> Bot::getPossibleMoves(Board* board) const
{
    std::vector<Move> moves;
    if (board == nullptr) return moves;

    for (int x = 0; x < Board::NB_ROW; ++x) {
        for (int y = 0; y < Board::NB_COL; ++y) {
            for (int s = 0; s <= static_cast<int>(SIZE::LARGE); ++s) {
                SIZE size = static_cast<SIZE>(s);
                /* Le bot doit avoir au moins un pion de cette taille (une de ses couleurs). */
                bool hasPionSize = false;
                for (COLOR c : color) {
                    if (hasPion(c, size)) { hasPionSize = true; break; }
                }
                if (hasPionSize && board->canPlacePion(x, y, size))
                    moves.push_back({x, y, size});
            }
        }
    }
    return moves;
}



/**
 * @brief Tour de jeu du bot selon cette stratégie : 
 1) gagner si possible
 2) bloquer un adversaire qui pourrait gagner 
 3) sinon jouer un coup aléatoire parmi les coups possibles. 
 */
playerAction_t Bot::playTurn(Board* board, cursor_t* cursor)
{
    if (board == nullptr || cursor == nullptr) return PION_SEL_DISABLE;

    std::vector<Move> possible = getPossibleMoves(board);
    if (possible.empty()) return PION_SEL_DISABLE;

    COLOR myColor = color[0];

    // Possibilité de gagner immédiatement
    for (const Move& m : possible) {
        if (hasPion(myColor, m.size) && board->wouldWin(m.x, m.y, myColor, m.size)) {
            cursor->x = m.x;
            cursor->y = m.y;
            board->addPion(m.x, m.y, {myColor, m.size});
            usePion(myColor, m.size);
            return ENDPLAY;
        }
    }

    // Bloquer l'adversaire
    std::vector<COLOR> opponents = board->getOpponentColors(myColor);
    for (COLOR oppColor : opponents) {
        for (const Move& m : possible) {
            if (hasPion(myColor, m.size) && board->wouldOpponentWin(m.x, m.y, oppColor, m.size)) {
                cursor->x = m.x;
                cursor->y = m.y;
                board->addPion(m.x, m.y, {myColor, m.size});
                usePion(myColor, m.size);
                return ENDPLAY;
            }
        }
    }

    // Jouer aléatoirement parmi les coups possibles
    static std::mt19937 rng(static_cast<unsigned>(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<size_t> dist(0, possible.size() - 1);
    const Move& m = possible[dist(rng)];
    cursor->x = m.x;
    cursor->y = m.y;
    board->addPion(m.x, m.y, {myColor, m.size});
    usePion(myColor, m.size);
    return ENDPLAY;
}



/**
 * @brief Stocke dans previsionsCoups les 3 prochains coups qui peuvent
 * permettre au bot de gagner.
 */
void Bot::nextMove(Board* board)
{
    previsionsCoups.clear();
    if (board == nullptr) return;

    std::vector<Move> possible = getPossibleMoves(board);
    if (possible.empty()) return;

    COLOR myColor = color[0];

    /* Étape 1 : coups qui font gagner immédiatement */
    for (const Move& m : possible) {
        if (previsionsCoups.size() >= 3) return;
        if (hasPion(myColor, m.size) && board->wouldWin(m.x, m.y, myColor, m.size))
            previsionsCoups.push_back(m);
    }

    /* Étape 2 : coups qui bloquent un adversaire */
    std::vector<COLOR> opponents = board->getOpponentColors(myColor);
    auto alreadyStored = [this](int x, int y, SIZE sz) {
        for (const Move& prev : previsionsCoups)
            if (prev.x == x && prev.y == y && prev.size == sz) return true;
        return false;
    };
    for (COLOR oppColor : opponents) {
        if (previsionsCoups.size() >= 3) return;
        for (const Move& m : possible) {
            if (previsionsCoups.size() >= 3) return;
            if (!alreadyStored(m.x, m.y, m.size) && hasPion(myColor, m.size) &&
                board->wouldOpponentWin(m.x, m.y, oppColor, m.size))
                previsionsCoups.push_back(m);
        }
    }

    /* Étape 3 : compléter avec des coups possibles (sans doublon). */
    for (const Move& m : possible) {
        if (previsionsCoups.size() >= 3) return;
        if (!alreadyStored(m.x, m.y, m.size))
            previsionsCoups.push_back(m);
    }
}
