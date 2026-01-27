/**
 * @file Pion.hpp
 * @brief Structure représentant un pion du jeu
 * @version 0.1
 * @date 2026-01-27
 * @copyright Copyright (c) 2026
 */
#pragma once

#include "Color.hpp"
#include "Size.hpp"

/**
 * @struct Pion
 * @brief Structure représentant un pion du jeu avec sa couleur et sa taille
 */
typedef struct
{
    COLOR Color;
    SIZE taille;
} Pion;
