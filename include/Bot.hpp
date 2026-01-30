#ifdef BOT_HPP
#define BOT_HPP

#include "Player.h"

/**
 * @brief
 * Classe Bot qui hérite de Player
 * Le bot joue automatiquement ses tours
 */
class Bot : public Player
{
private:
public:
    /**
     * @brief
     * Constructeur du Bot
     */
    Bot(std::string name, COLOR color);
    /**
     * @brief
     * Destructeur du Bot
     */
    ~Bot();

    enum playTurn();
    void nextMove();

    getPossibleMoves(Board &board); // renvoie une liste des coups possibles
};

#endif