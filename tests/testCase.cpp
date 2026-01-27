/**
 * @file testCase.cpp
 * @brief Tests unitaires pour la classe Case
 * @version 0.1
 * @date 2026-01-27
 * @copyright Copyright (c) 2026
 */

#include <iostream>
#include <cassert>
#include "../include/Case.hpp"
#include "../include/Pion.hpp"

void testCaseConstruction()
{
    std::cout << "Test: Construction d'une case..." << std::endl;
    
    Case testCase(1, 2);
    
    assert(testCase.getX() == 1);
    assert(testCase.getY() == 2);
    
    std::cout << "✓ Construction de la case (1, 2) réussie" << std::endl;
}

void testCaseAddPion()
{
    std::cout << "Test: Ajout de pions..." << std::endl;
    
    Case testCase(0, 0);
    
    // Créer et ajouter un pion SMALL
    Pion* smallPion = new Pion{RED, SMALL};
    testCase.addPion(smallPion);
    
    // Créer et ajouter un pion MEDIUM
    Pion* mediumPion = new Pion{BLUE, MEDIUM};
    testCase.addPion(mediumPion);
    
    // Créer et ajouter un pion LARGE
    Pion* largePion = new Pion{GREEN, LARGE};
    testCase.addPion(largePion);
    
    std::cout << "✓ Ajout de pions réussi (SMALL, MEDIUM, LARGE)" << std::endl;
}

void testCaseReplacePion()
{
    std::cout << "Test: Remplacement de pions..." << std::endl;
    
    Case testCase(1, 1);
    
    // Ajouter un premier pion SMALL
    Pion* pion1 = new Pion{RED, SMALL};
    testCase.addPion(pion1);
    
    // Remplacer par un autre pion SMALL
    Pion* pion2 = new Pion{BLUE, SMALL};
    testCase.addPion(pion2);
    
    std::cout << "✓ Remplacement de pions réussi" << std::endl;
}

void testCaseDeletePion()
{
    std::cout << "Test: Suppression de pions..." << std::endl;
    
    Case testCase(0, 0);
    
    // Ajouter des pions
    Pion* smallPion = new Pion{RED, SMALL};
    Pion* mediumPion = new Pion{BLUE, MEDIUM};
    
    testCase.addPion(smallPion);
    testCase.addPion(mediumPion);
    
    // Supprimer le pion SMALL
    testCase.deletePion(SMALL);
    
    std::cout << "✓ Suppression de pions réussie" << std::endl;
}


void testCaseGetCoordinates()
{
    std::cout << "Test: Accesseurs de coordonnées..." << std::endl;
    
    // Tester plusieurs positions
    Case case1(0, 0);
    assert(case1.getX() == 0 && case1.getY() == 0);
    
    Case case2(1, 2);
    assert(case2.getX() == 1 && case2.getY() == 2);
    
    Case case3(2, 2);
    assert(case3.getX() == 2 && case3.getY() == 2);
    
    std::cout << "✓ Accesseurs de coordonnées réussis" << std::endl;
}

void testCaseFullIntegration()
{
    std::cout << "Test: Intégration complète..." << std::endl;
    
    Case testCase(1, 1);
    
    // Ajouter 3 pions de différentes tailles
    Pion* pion1 = new Pion{RED, SMALL};
    Pion* pion2 = new Pion{BLUE, MEDIUM};
    Pion* pion3 = new Pion{GREEN, LARGE};
    
    testCase.addPion(pion1);
    testCase.addPion(pion2);
    testCase.addPion(pion3);
    
    // Vérifier les coordonnées
    assert(testCase.getX() == 1);
    assert(testCase.getY() == 1);
    
    // Supprimer un pion
    testCase.deletePion(MEDIUM);
    
    std::cout << "✓ Intégration complète réussie" << std::endl;
}


void testCase()
{
    std::cout << "\n========== TESTS CASE ===========" << std::endl;
    
    try {
        testCaseConstruction();
        testCaseGetCoordinates();
        testCaseAddPion();
        testCaseReplacePion();
        testCaseDeletePion();
        testCaseFullIntegration();
        
        std::cout << "\n✓ Tous les tests de Case sont passés!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "\n✗ Erreur lors des tests: " << e.what() << std::endl;
    }
}
