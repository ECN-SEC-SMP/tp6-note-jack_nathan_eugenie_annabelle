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
    Bot(std::string name, COLOR color);
    ~Bot();
    
    enum playTurn();
    void nextMove();


};

#endif