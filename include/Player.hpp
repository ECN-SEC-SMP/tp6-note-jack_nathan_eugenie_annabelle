#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <string>
#include <vector>
#include <Pion.hpp>
#include <Size.hpp>
#include <Color.hpp>

#include "Board.hpp"

typedef enum{
    ENDPLAY,
    ARROW,
    PION_SEL_ENABLE,
    PION_SEL_DISABLE,
} playerAction_t;

typedef struct {
    int x;
    int y;
    SIZE s;
    COLOR c;
} cursor_t;

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
     * @brief Couleur pion : gère le cas "2 joueurs" -> chacun possède 2 couleurs
     *
     */
    std::vector<COLOR> color;

    /**
     * @brief pion encore disponibles
     *
     */
    std::vector<Pion*> stock[3];

public:
    /**
     * @brief Construit le joueur
     * 
     * -> assignedColor = 1 : 1 seul couleur
     * -> assignedColor = 1 : 2 couleur
     *
     */
    Player(const std::string name, std::vector<COLOR> assignedColor);
    ~Player();

    // Getters
    std::string getName() const { return name; }
    const std::vector<COLOR>& getColor() const { return color; }

    bool hasPion(COLOR c, SIZE s) const;
    
    void usePion(COLOR c, SIZE s);

    /**
     * @brief Méthode virtuelle pure : implémentée diff pour un Humain (saisie clavier) ou un Bot (IA) 
     */
    virtual playerAction_t playTurn(Board* board, cursor_t* cursor) = 0;
};

#endif