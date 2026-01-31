/**
 * @file Player.cpp
 * @brief 
 */

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <assert.h>
#include "Player.hpp"

Player::Player(const std::string name, std::vector<COLOR> assignedColor): name(name), color(assignedColor)
{
    Pion* newPion = nullptr;

    for(COLOR c : color){
        for(int i = 0; i < 3; i++)
        {
            newPion = nullptr;
            newPion = (Pion*)malloc(sizeof(Pion));
            assert(newPion != nullptr);
            newPion->Color = c;
            newPion->taille = SIZE::SMALL;
            stock[SIZE::SMALL].push_back(newPion);
            
            newPion = nullptr;
            newPion = (Pion*)malloc(sizeof(Pion));
            assert(newPion != nullptr);
            newPion->Color = c;
            newPion->taille = SIZE::MEDIUM;
            stock[SIZE::MEDIUM].push_back(newPion);

            newPion = nullptr;
            newPion = (Pion*)malloc(sizeof(Pion));
            assert(newPion != nullptr);
            newPion->Color = c;
            newPion->taille = SIZE::LARGE;
            stock[SIZE::LARGE].push_back(newPion);
        }
    }
}

Player::~Player(void) {

    // Free all remaining Pion*
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < this->stock[i].size(); j++)
        {
            if (this->stock[i].at(j) != nullptr) {
                free(this->stock[i].at(j));
            }
        }
    }
}

/**
 * @brief Vérifie s'il reste au moins un pion d'une couleur et taille précise
 */
bool Player::hasPion(COLOR c, SIZE s) const {

    for (const Pion* pion : stock[s]) {
        if (pion->Color == c) return true;
    }
    return false;
}

/**
 * @brief Retire un pion du stock après qu'il a été placé sur le plateau 
 */
void Player::usePion(COLOR c, SIZE s) {

    if (this->stock[s].empty()) {
        return;
    }

    uint16_t i = 0;
    for (auto it = this->stock[s].begin(); it != this->stock[s].end(); it++, i++) {
        if (this->stock->at(i)->Color == c) {
            this->stock[s].erase(it);
            break;
        }
    }

    return;
}