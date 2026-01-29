#ifndef _GAMEHANDLER_HPP_
#define _GAMEHANDLER_HPP_

#include <vector>
#include <iostream>

#include "Case.hpp"
#include "Board.hpp"
#include "Human.hpp"

#define MAX_PLAYER 4
#define MIN_PLAYER 1

class GameHandler
{

private:
    int currentPlayer;

    std::vector<Player *> players;
    Board *board;

    /**
     * @brief Vérifie si un joueur a gagné
     *
     * @param box
     * @return true
     * @return false
     */
    bool detectWin(Case *box);
    void refreshDisplay(void);

    COLOR getRandomColor();

    /**
     * @brief Configure le jeu
     *
     * Nombre de joueurs et nombre de robots
     */
    void setup(void);

    /**
     * @brief Configure le nom des joueurs
     *
     */
    void joueursNoms(void);

    /**
     * @brief Récupère un entier aléatoire entre l'intervale défini
     *
     * @param min Valeur minimale
     * @param max Valeur maximale
     * @return int
     */
    int getRandom(int min, int max);

    /**
     * @brief Assigne la couleur à chacun des joueurs
     *
     */
    void assignColor(void);

    bool detectWin(int x, int y, COLOR c) const;

    bool checkRow(int x, COLOR c) const;
    bool checkCol(int y, COLOR c) const;
    bool checkDiagMain(COLOR c) const;
    bool checkDiagAnti(COLOR c) const;
    bool checkStack(int x, int y, COLOR c) const;

    // helper de lecture
    bool has(int x, int y, SIZE s, COLOR c) const;

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