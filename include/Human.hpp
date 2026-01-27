#ifndef _HUMAN_HPP_
#define _HUMAN_HPP_ 

#include <string>
#include <vector>
#include <Player.hpp>
#include "Input.hpp"

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

    playerAction_t playTurn(Board* board, cursor_t* cursor)
    {
        static cursor_t cursor = {0};
        InputKey_t key;
        COLOR c = color[0]; // Par défaut première couleur
        SIZE s = SIZE::MEDIUM;
        // 1. Déplacement du curseur (Simulation d'entrée clavier)
        Input* input = Input::GetInstance();

        input->begin();

        key = input->waitCtrlKey();
        
        // 2. Logique de sélection (exemple simplifié)
        // Si le joueur appuie sur une touche de direction : return ARROW;
        
        // TODO : Add define for '2'
        if (ARROW_UP == key) {
            if (cursor->x < 2) {
                cursor->x++;
            }
            goto retArrow;
        }

        // 3. Si le joueur valide un placement :

        if (hasPion(c, s) && ???(cursor->x, cursor->y, s)) {
            board->addPion(cursor->x, cursor->y, {c, s});
            usePion(c, s);
            return ENDPLAY; // Fin du tour
        }
        
        return PION_SEL_ENABLE; // Le joueur continue de choisir
retArrow:
        return ARROW;
    }
    
    /**
     * @brief retourne le nom du joueur
     *
     */
    std::string getCursor() const{return ; }
};

#endif