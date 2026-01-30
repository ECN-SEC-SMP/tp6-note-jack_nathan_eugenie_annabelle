/**
 * @file Display.hpp
 * @author Nathan
 * @brief 
 * @version 0.1
 * @date 2026-01-20
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>
#include <string>

#include "Pion.hpp"

#define NB_ROW  3
#define NB_COL  3

// Dimenions
#define CANVAS_CASE_SIZE 5
#define CANVAS_WALL_SIZE 1
#define CANVAS_SIZE      ((CANVAS_CASE_SIZE * 3) + (CANVAS_WALL_SIZE * 4))

#define DISPLAY_SELECT_NONE -1

// TODO : REMOVE WHEN CASE IS IMPLEMENTED
typedef Pion Case[3];

class Display
{
private:

    Case board[NB_ROW][NB_COL];
    
    std::string printBuff[CANVAS_SIZE][CANVAS_SIZE];
    std::string pionSelPrintBuff[CANVAS_SIZE][CANVAS_CASE_SIZE + (2*CANVAS_WALL_SIZE)];

    int8_t selx;
    int8_t sely;

    bool pionSelEn;
    enum SIZE selPion;

    /**
     * @brief Affiche la grille
     * 
     */
    void loadGrille(void);

    /**
     * @brief Affiche une case
     * 
     * @param x 
     * @param y 
     */
    void loadCase(void);

    /**
     * @brief Load selection display on a case, based on selx and sely
     * 
     */
    void loadSelectedCase(void);

    /**
     * @brief Load Small circle from top left corner of a case
     * 
     * @param topLeftCorner 
     */
    void loadCircleSmall(uint8_t topLefCornerX, uint8_t topLefCornerY, std::string colorCode);

    /**
     * @brief Load Medium circle from top left corner of a case
     * 
     * @param topLeftCorner 
     */
    void loadCircleMedium(uint8_t topLefCornerX, uint8_t topLefCornerY, std::string colorCode);

    /**
     * @brief Load Large case from top left corner of a case
     * 
     * @param topLeftCorner 
     */
    void loadCircleLarge(uint8_t topLefCornerX, uint8_t topLefCornerY, std::string colorCode);

    /**
     * @brief Load Pion size selection
     * 
     * @param pionSize 
     */
    void loadSelectedPion(enum SIZE pionSize);

public:
    Display(/* args */);
    ~Display();

    /**
     * @brief Affiche Board
     * 
     */
    void print(/* Board brd */);

    /**
     * @brief Active ou non l'affichage de la selection des Pions
     * 
     * @param enable true affiche, false efface
     */
    void printPionSelection(bool enable);

    /**
     * @brief Met le curseur à la position x,y sur la grille
     * 
     * @param x 
     * @param y 
     */
    void setCursor(uint8_t x, uint8_t y);

    // TODO : la valeur peut changer quand Pion sera implémenté
    /**
     * @brief 
     * 
     *
     * 
     * @param size SMALL, MEDIUM, LARGE
     */
    void setCursor(enum SIZE size);

    /**
     * @brief Pose un pion sur l'affichage 
     * 
     */
    void addPion(Pion pion, uint8_t x, uint8_t y);

    /**
     * @brief Demande le nombre de joueur voulu
     * 
     * @return uint8_t Retourne le nombre de joueur 2 à 4
     */
    uint8_t getNbPlayers(uint8_t min, uint8_t max);

    /**
     * @brief Demande le nombre de robot voulu
     * 
     * @return uint8_t 
     */
    uint8_t getNbRobot(uint8_t min, uint8_t max);

    /**
     * @brief Demande une suite de caractère
     * 
     * @param question Message à afficher avant
     * @return std::string reponse du joueur
     */
    std::string getString(std::string question);

};

#endif  /* DISPLAY_H_ */