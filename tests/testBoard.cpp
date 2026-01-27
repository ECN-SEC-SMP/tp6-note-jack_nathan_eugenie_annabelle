/**
 * @file testBoard.cpp
 * @brief Tests unitaires pour la classe Board
 * @version 0.1
 * @date 2026-01-27
 * @copyright Copyright (c) 2026
 */

#include <iostream>
#include <cassert>
#include "Board.hpp"


void testBoardConstruction()
{
    std::cout << "Test: Construction du plateau..." << std::endl;
    
    Board board;
    
    // Vérifier que les cases sont correctement initialisées
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            Case c = board.getCase(x, y);
            assert(c.getX() == x);
            assert(c.getY() == y);
        }
    }
    
    std::cout << "✓ Construction du plateau réussie" << std::endl;
}

void testBoardGetCase()
{
    std::cout << "Test: Récupération des cases..." << std::endl;
    
    Board board;
    
    // Tester différentes positions
    Case case00 = board.getCase(0, 0);
    assert(case00.getX() == 0 && case00.getY() == 0);
    
    Case case12 = board.getCase(1, 2);
    assert(case12.getX() == 1 && case12.getY() == 2);
    
    Case case22 = board.getCase(2, 2);
    assert(case22.getX() == 2 && case22.getY() == 2);
    
    std::cout << "✓ Récupération des cases réussie" << std::endl;
}

void testBoardIntegration()
{
    std::cout << "Test: Intégration du plateau..." << std::endl;
    
    Board board;
    int count = 0;
    
    // Parcourir toutes les cases et vérifier qu'elles sont initialisées
    for (int x = 0; x < BOARD_SIZE; x++) {
        for (int y = 0; y < BOARD_SIZE; y++) {
            Case c = board.getCase(x, y);
            count++;
        }
    }
    
    assert(count == BOARD_SIZE * BOARD_SIZE);
    std::cout << "✓ Plateau contient " << count << " cases correctement initialisées" << std::endl;
}

void testBoard()
{
    std::cout << "\n========== TESTS BOARD ==========" << std::endl;
    
    try {
        testBoardConstruction();
        testBoardGetCase();
        testBoardIntegration();
        
        std::cout << "\n✓ Tous les tests du plateau sont passés!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "\n✗ Erreur lors des tests: " << e.what() << std::endl;
    }
}
