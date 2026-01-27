#ifndef _HUMAN_HPP_
#define _HUMAN_HPP_ 

#include <string>
#include <vector>
#include <Player.hpp>


struct Cursor
{
    int x;
    int y;    
};


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
    Human(const std::string& name, COLOR color) : Player(name, color) {}
    
    /**
     * @brief retourne le nom du joueur
     *
     */
    std::string getCursor() const{return ; }
};

#endif