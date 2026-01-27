#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <string>
#include <vector>
#include <Pion.hpp>
#include <Size.hpp>
#include <Color.hpp>


/**
 * @brief 
 *
 */
class Player
{
protected:
    /**
     * @brief  Nom Joueur
     *
     */
    std::string name;

    /**
     * @brief Couleur pion
     *
     */
    COLOR color;

    /**
     * @brief pointeur vers Board
     *
     */
    Board* board;

    /**
     * @brief pion encore disponibles
     *
     */
    std::vector<Pion> stock;

public:
    /**
     * @brief Construct a new Carte object
     *
     */
    Player(const std::string name, COLOR color): name(name), color(color)
    {
        for(int i = 0; i < 3; i++){
            stock.push_back({color, SIZE::SMALL});
            stock.push_back({color, SIZE::MEDIUM});
            stock.push_back({color, SIZE::LARGE});
        }
    }

    virtual ~Player()=default;

    // Getters
    std::string getName() const { return name; }
    COLOR getColor() const { return color; }

    /**
     * @brief Vérifie s'il reste au moins un pion d'une certaine taille 
     */
    bool hasPion(SIZE s) const {
        for (const auto& p : stock) {
            if (p.taille == s) return true;
        }
        return false;
    }
    
    /**
     * @brief Retire un pion du stock après qu'il a été placé sur le plateau 
     */
    void removePion(SIZE s) {
        for (auto it = stock.begin(); it != stock.end(); ++it) {
            if (it->taille == s) {
                stock.erase(it);
                return;
            }
        }
    }

    /**
     * @brief Méthode virtuelle pure : sera implémentée différemment pour un Humain (saisie clavier) ou un Bot (IA) 
     */
    virtual void playTurn(Board& board) = 0;
};

#endif