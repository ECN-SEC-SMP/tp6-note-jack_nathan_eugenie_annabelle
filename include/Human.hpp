#ifndef _HUMAN_HPP_
#define _HUMAN_HPP_ 

#include <string>
#include <vector>
#include "Player.hpp"
#include "Input.hpp"
#include "Board.hpp"
#include "Case.hpp"

/**
 * @brief Classe Human
 *
 */
class Human : public Player
{
public:
    /**
     * @brief Constructeur utilisant celui de la classe mère (Player)
     */
    Human(const std::string& name, std::vector<COLOR> color) : Player(name, color) {}

    playerAction_t playTurn(Board* board, cursor_t* cursor);
 
};

#endif