/**
 * @file Player.cpp
 * @brief 
 */

#include <iostream>
#include <string>
#include <vector>
#include "Player.hpp"

Player::Player(const std::string name, std::vector<COLOR> assignedColor): name(name), color(assignedColor)
{
    for(COLOR c : color){
        for(int i = 0; i < 3; i++)
        {            
            stock.push_back({c, SIZE::SMALL});
            stock.push_back({c, SIZE::MEDIUM});
            stock.push_back({c, SIZE::LARGE});
        }
    }
}

/**
 * @brief Vérifie s'il reste au moins un pion d'une couleur et taille précise
 */
bool Player::hasPion(COLOR c, SIZE s) const {
    for (const auto& pion : stock) {
        if (pion.Color == c && pion.taille == s) return true;
    }
    return false;
}

/**
 * @brief Retire un pion du stock après qu'il a été placé sur le plateau 
 */
void Player::usePion(COLOR c, SIZE s) {
    for (auto it = stock.begin(); it != stock.end(); ++it) {
        if (it->taille == s) {
            stock.erase(it);
            return;
        }
    }
}