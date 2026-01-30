#include "Bot.hpp"
#include "Pion.hpp"
#include <algorithm>
#include <random>
#include <chrono>

Bot::Bot(const std::string& name, COLOR color) : Player(name, {color}) {}

Bot::Bot(const std::string& name, std::vector<COLOR> assignedColor) : Player(name, assignedColor) {}

Bot::~Bot() {}

/**
 * @brief Vérifie si la case (i, j) a au moins un pion de la couleur c,
 * ou si (i, j) est la case où on place le pion (x, y) de couleur c.
 */
static bool cellHasColor(Board* board, int i, int j, COLOR c, int placeX, int placeY)
{
    if (i == placeX && j == placeY) return true;
    Case cell = board->getCase(i, j);
    for (int s = 0; s <= static_cast<int>(LARGE); ++s) {
        Pion* p = cell.getPion(static_cast<SIZE>(s));
        if (p != nullptr && p->Color == c) return true;
    }
    return false;
}

/**
 * @brief Vérifie s’il y a 3 cases alignées (ligne, colonne ou diagonale) de la couleur c
 * en considérant un pion (c, s) placé en (x, y).
 */
bool Bot::wouldWin(Board* board, int x, int y, COLOR c, SIZE s) const
{
    (void)s;
    if (board == nullptr) return false;
    const int N = Board::NB_ROW;
    /* Lignes */
    for (int i = 0; i < N; ++i) {
        if (cellHasColor(board, i, 0, c, x, y) &&
            cellHasColor(board, i, 1, c, x, y) &&
            cellHasColor(board, i, 2, c, x, y))
            return true;
    }
    /* Colonnes */
    for (int j = 0; j < N; ++j) {
        if (cellHasColor(board, 0, j, c, x, y) &&
            cellHasColor(board, 1, j, c, x, y) &&
            cellHasColor(board, 2, j, c, x, y))
            return true;
    }
    /* Diagonale \ */
    if (cellHasColor(board, 0, 0, c, x, y) &&
        cellHasColor(board, 1, 1, c, x, y) &&
        cellHasColor(board, 2, 2, c, x, y))
        return true;
    /* Diagonale / */
    if (cellHasColor(board, 0, 2, c, x, y) &&
        cellHasColor(board, 1, 1, c, x, y) &&
        cellHasColor(board, 2, 0, c, x, y))
        return true;
    return false;
}

void Bot::addPion(Board* board, int x, int y, const Pion& p) const
{
    if (board == nullptr) return;
    board->addPion(x, y, p);
}

std::vector<COLOR> Bot::getOpponentColors(Board* board, COLOR myColor) const
{
    (void)board;
    std::vector<COLOR> out;
    if (myColor != RED)   out.push_back(RED);
    if (myColor != BLUE)  out.push_back(BLUE);
    if (myColor != GREEN) out.push_back(GREEN);
    if (myColor != YELLOW) out.push_back(YELLOW);
    return out;
}

bool Bot::wouldOpponentWin(Board* board, int x, int y, COLOR opponentColor, SIZE s) const
{
    if (board == nullptr) return false;
    return wouldWin(board, x, y, opponentColor, s);
}

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
                /* On peut placer si la case (x,y) n’a pas encore de pion de cette taille. */
                bool canPlace = (x >= 0 && x < Board::NB_ROW && y >= 0 && y < Board::NB_COL);
                if (canPlace) {
                    Case cell = board->getCase(x, y);
                    canPlace = (cell.getPion(size) == nullptr);
                }
                if (hasPionSize && canPlace)
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
        if (hasPion(myColor, m.size) && wouldWin(board, m.x, m.y, myColor, m.size)) {
            cursor->x = m.x;
            cursor->y = m.y;
            addPion(board, m.x, m.y, {myColor, m.size});
            usePion(myColor, m.size);
            return ENDPLAY;
        }
    }

    // Bloquer l'adversaire
    std::vector<COLOR> opponents = getOpponentColors(board, myColor);
    for (COLOR oppColor : opponents) {
        for (const Move& m : possible) {
            if (hasPion(myColor, m.size) && wouldOpponentWin(board, m.x, m.y, oppColor, m.size)) {
                cursor->x = m.x;
                cursor->y = m.y;
                addPion(board, m.x, m.y, {myColor, m.size});
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
    addPion(board, m.x, m.y, {myColor, m.size});
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
        if (hasPion(myColor, m.size) && wouldWin(board, m.x, m.y, myColor, m.size))
            previsionsCoups.push_back(m);
    }

    /* Étape 2 : coups qui bloquent un adversaire */
    std::vector<COLOR> opponents = getOpponentColors(board, myColor);
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
                wouldOpponentWin(board, m.x, m.y, oppColor, m.size))
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
