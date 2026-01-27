#ifndef _GAMEHANDLER_HPP_
#define _GAMEHANDLER_HPP_

#include <vector>
#include <iostream>

#include "Case.hpp"
#include "Board.hpp"

#define MAX_PLAYER 4
#define MIN_PLAYER 1

class GameHandler
{

private:
    int currentPlayer;

    // std::vector<Player*> players;
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

    bool checkDiagR(int x, int y);
    bool checkDiagL(int x, int y);
    bool checkLineHB(int x, int y);
    bool checkLineLR(int x, int y);
    bool checkCase(int x, int y);

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