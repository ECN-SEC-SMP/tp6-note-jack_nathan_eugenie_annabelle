/**
 * @file Case.hpp
 * @brief Classe représentant une case du plateau de jeu
 * @version 0.1
 * @date 2026-01-27
 * @copyright Copyright (c) 2026
 */
#pragma once

#include "Pion.hpp"
#include "Size.hpp"

/**
 * @class Case
 * @brief Classe représentant une case du plateau qui peut contenir jusqu'à 3 pions de tailles différentes
 */
class Case
{
private:
    Pion* pion[3]; ///< Tableau de pointeurs vers les pions
    int x;         
    int y;         
public:
    /**
     * @brief Constructeur de base d'une case
     */
    Case();
    /**
     * @brief Constructeur d'une case
     * @param x Coordonnée X de la case
     * @param y Coordonnée Y de la case
     */
    Case(int x, int y);
    
    /**
     * @brief Destructeur d'une case
     * Supprime tous les pions contenus dans la case
     */
    ~Case();
    
    /**
     * @brief Ajoute un pion à la case
     * @param p Pointeur vers le pion à ajouter
     */
    void addPion(Pion* p);
    
    /**
     * @brief Supprime un pion de la case selon sa taille
     * @param s Taille du pion à supprimer
     */
    void deletePion(SIZE s);

    /**
     * @brief Renvoie le Pion ou nullptr si vide
     * @param s Taille du pion à renvoyer
     */
    Pion* getPion(SIZE s);
    
    /**
     * @brief Récupère la coordonnée X de la case
     * @return int Coordonnée X
     */
    int getX();
    
    /**
     * @brief Récupère la coordonnée Y de la case
     * @return int Coordonnée Y
     */
    int getY();
};
