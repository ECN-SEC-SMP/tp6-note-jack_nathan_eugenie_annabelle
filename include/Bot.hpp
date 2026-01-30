#ifndef BOT_HPP
#define BOT_HPP

#include "Player.hpp"
#include "board.h"
#include "Size.hpp"
#include <vector>

/**
 * @brief Représente un coup possible sur le plateau (position + taille du pion).
 */
struct Move
{
    int x; 
    int y;   
    SIZE size;
};

/**
 * @brief Classe Bot qui hérite de Player.
 * Le bot joue automatiquement ses tours.
 */
class Bot : public Player
{
private:
    /**
     * Prévisions des 3 prochains coups qui peuvent permettre au bot de gagner.
     */
    std::vector<Move> previsionsCoups;

public:
    // Constructeur : 1 couleur (bot contre 1 ou plusieurs joueurs).
    Bot(const std::string& name, COLOR color);
    // Constructeur : plusieurs couleurs (bot avec 2 couleurs en mode 2v2).
    Bot(const std::string& name, std::vector<COLOR> assignedColor);
    ~Bot();

    playerAction_t playTurn(Board* board, cursor_t* cursor) override;

    /**
     * Prévision des 3 prochains coups qui peuvent permettre au bot de gagner.
     * Stocke dans previsionsCoups
     */
    void nextMove(Board* board);

    // Renvoie la liste des coups possibles.
    std::vector<Move> getPossibleMoves(Board* board) const;
};

#endif
