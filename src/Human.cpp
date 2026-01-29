/**
 * @file Human.cpp
 * @brief 
 */

#include <iostream>
#include <string>
#include <vector>
#include "Human.hpp"
#include "Board.hpp"

playerAction_t Human::playTurn(Board* board, cursor_t* cursor)
    {
        static cursor_t cursor = {0};
        InputKey_t key;
        Input* input = Input::GetInstance();
        key = input->waitCtrlKey();
        
        // Déplacements
        if (ARROW_UP == key) {
            if (cursor->x < 2) {
                cursor->x++;
            }
            return ARROW;
        }
        if (ARROW_DOWN == key) {
            if (cursor->x > 0) {
                cursor->x--;
            }
            return ARROW;
        }
        if (ARROW_RIGHT == key) {
            if (cursor->y < 2) {
                cursor->y++;
            }
            return ARROW;
        }
        if (ARROW_LEFT == key) {
            if (cursor->y > 0) {
                cursor->y--;
            }
            return ARROW;
        }
        //if(key == KEY_TAB) {
        //    return PION_SEL_ENABLE;
        //}

        if(key == KEY_ENTER){
            COLOR c = this->color[0]; //Première couleur du joueur
            SIZE s = SIZE::MEDIUM; //Par défaut taille Medium
            
            if (!hasPion(c, s)) {
                return PION_SEL_DISABLE;
            }
            Case selectedCase = board->getCase(cursor->x, cursor->y);
        
            if (selectedCase.getPion(s) == nullptr) {
                Pion* newPion = new Pion{c, s};
                selectedCase.addPion(newPion);
                usePion(c, s);
                
                return ENDPLAY;
            }
        }

        return ARROW;
    }