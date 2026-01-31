#ifndef _GAMEHANDLER_HPP_
#define _GAMEHANDLER_HPP_

#include <vector>
#include <iostream>

#include "Case.hpp"
#include "Board.hpp"
#include "Human.hpp"
#include "Display.hpp"

#define MAX_PLAYER 4
#define MIN_PLAYER 1

class GameHandler
{

private:
    int currentPlayer;

    std::vector<Player *> players;
    Board board;

    /**
     * @brief Récupère une couleur aléatoire qui n'est pas déjà utilisé par un autre joueur
     * 
     * @return COLOR 
     */
    COLOR getRandomColor();

    /**
     * @brief Configure le jeu
     *
     * Nombre de joueurs et nombre de robots
     */
    void setup(void);

    /**
     * @brief Detecte la victoire
     *
     * @param x Position X du dernier pion joué sur la board
     * @param y Position Y du dernier pion joué sur la board
     * @param c Couleur du dernier pion joué
     * @return true
     * @return false
     */
    bool detectWin(int x, int y, COLOR c);

    /**
     * @brief Vérifie la ligne d'une board
     *
     * @param x Position X du pion joué sur la board
     * @param c Couleur du pion joué
     * @return true
     * @return false
     */
    bool checkRow(int x, COLOR c);

    /**
     * @brief Vérifie la colonne d'une board
     *
     * @param x Position Y du pion joué sur la board
     * @param c Couleur du pion joué
     * @return true
     * @return false
     */
    bool checkCol(int y, COLOR c);

    /**
     * @brief Vérifie la diagonale gauche-droite sur la board
     *
     * @param c Couleur du pion joué
     * @return true
     * @return false
     */
    bool checkDiagMain(COLOR c);

    /**
     * @brief Vérifie la diagonale droite-gauche sur la board
     *
     * @param c Couleur du pion joué
     * @return true
     * @return false
     */
    bool checkDiagAnti(COLOR c);

    /**
     * @brief Vérifie l'empilement des pions une case sur la board
     *
     * @param x Position X du dernier pion joué sur la board
     * @param y Position Y du dernier pion joué sur la board
     * @param c Couleur du pion joué
     * @return true
     * @return false
     */
    bool checkStack(int x, int y, COLOR c);

    /**
     * @brief Vérifie si une `Case` contient un pion
     *
     * @param x Position X du pion
     * @param y Position Y du pion
     * @param s Taille du pion
     * @param c Couleur du pion
     * @return true
     * @return false
     */
    bool has(int x, int y, SIZE s, COLOR c);

public:
    /**
     * @brief Constructeur du jeu
     *
     */
    GameHandler(void);

    /**
     * @brief Destructeur du jeu
     *
     */
    ~GameHandler();

    /**
     * @brief Démarre le jeu
     *
     */
    void start(void);
};

#endif