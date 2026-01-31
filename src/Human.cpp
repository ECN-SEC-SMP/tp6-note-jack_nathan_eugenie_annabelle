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
        static bool newTurn = true;
        static cursor_t _cursor = {0};
        static bool pionSelec = true;
        static SIZE sizeSelec = SMALL;
        static COLOR c = this->color[0]; // Par défault la première couleur
        InputKey_t key;
        Input* input = Input::GetInstance();

        if (newTurn) {
            cursor->x = _cursor.x;
            cursor->y = _cursor.y;
            cursor->s = _cursor.s;
            cursor->c = _cursor.c;
            input->begin();
            newTurn = false;
        }

        key = input->waitCtrlKey();

        // Mode selection
        if(key == KEY_SPACE) {
            if (pionSelec) {
                pionSelec = !pionSelec;
                cursor->s = sizeSelec;
                return PION_SEL_DISABLE;
            } else {
                pionSelec = !pionSelec;
                cursor->s = sizeSelec;
                return PION_SEL_ENABLE;
            }
        }

        // Choix du pion
        if (pionSelec) {
            
            if (ARROW_RIGHT == key) {
                if (sizeSelec == SMALL) {
                    if (this->hasPion(c, MEDIUM)) {
                        sizeSelec = MEDIUM;
                    } else if (this->hasPion(c, LARGE)) {
                        sizeSelec = LARGE;
                    } else {
                        sizeSelec = SMALL;
                    }
                } else if (sizeSelec == MEDIUM) {
                    if (this->hasPion(c, LARGE)) {
                        sizeSelec = LARGE;
                    } else {
                        sizeSelec = MEDIUM;
                    }
                }

                cursor->s = sizeSelec;
                return ARROW;
            }
            if (ARROW_LEFT == key) {
                if (sizeSelec == LARGE) {
                    if (this->hasPion(c, MEDIUM)) {
                        sizeSelec = MEDIUM;
                    } else if (this->hasPion(c, SMALL)) {
                        sizeSelec = SMALL;
                    } else {
                        sizeSelec = SMALL;
                    }
                } else if (sizeSelec == MEDIUM) {
                    if (this->hasPion(c, SMALL)) {
                        sizeSelec = SMALL;
                    } else {
                        sizeSelec = MEDIUM;
                    }
                }

                cursor->s = sizeSelec;
                return ARROW;
            }

        }
        // Choix de la position 
        else {
            // Déplacements
            if (ARROW_UP == key) {
                if (_cursor.x > 0) {
                    _cursor.x--;
                }
                cursor->x = _cursor.x;
                cursor->y = _cursor.y;
                return ARROW;
            }
            if (ARROW_DOWN == key) {
                if (_cursor.x < 2) {
                    _cursor.x++;
                }
                cursor->x = _cursor.x;
                cursor->y = _cursor.y;
                return ARROW;
            }
            if (ARROW_RIGHT == key) {
                if (_cursor.y < 2) {
                    _cursor.y++;
                }
                cursor->x = _cursor.x;
                cursor->y = _cursor.y;
                return ARROW;
            }
            if (ARROW_LEFT == key) {
                if (_cursor.y > 0) {
                    _cursor.y--;
                }
                cursor->x = _cursor.x;
                cursor->y = _cursor.y;
                return ARROW;
            }

            // Valide position
            if(key == KEY_ENTER) {
                Case selectedCase = board->getCase(_cursor.x, _cursor.y);
    
                if (selectedCase.getPion(sizeSelec) == nullptr) {
                    uint8_t idx;
                    for (idx = 0; idx < this->stock[sizeSelec].size(); idx++)
                    {
                        // Get the first pion with the right color
                        if (this->stock[sizeSelec].at(idx)->Color == c) {
                            break;
                        }
                    }
                    selectedCase.addPion(this->stock[sizeSelec][idx]);
                    this->usePion(c, sizeSelec);
                    
                    input->end();
                    newTurn = true; // End of play, ready for new turn

                    return ENDPLAY;
                }
            }
        }
        
        return ARROW;
    }