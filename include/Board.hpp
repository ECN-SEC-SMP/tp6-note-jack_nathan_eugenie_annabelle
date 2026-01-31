/**
 * @file Board.hpp
 * @brief Classe représentant le plateau de jeu
 * @version 0.1
 * @date 2026-01-27
 * @copyright Copyright (c) 2026
 */
#include "Case.hpp"

#define BOARD_SIZE 3 ///< Taille du plateau (3x3)

/**
 * @class Board
 * @brief Classe représentant le plateau de jeu contenant les cases
 */
class Board
{
private:
    Case cases[BOARD_SIZE][BOARD_SIZE]; ///< Matrice des cases du plateau
public:
    /**
     * @brief Constructeur du plateau
     * Initialise toutes les cases du plateau
     */
    Board();

    /**
     * @brief Destructeur du plateau
     */
    ~Board();

    /**
     * @brief Récupère une case du plateau
     * @param x Coordonnée X de la case (0-2)
     * @param y Coordonnée Y de la case (0-2)
     * @return Case La case aux coordonnées spécifiées
     */
    Case *getCase(int x, int y);
};
