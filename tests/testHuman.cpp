/**
 * @file testHuman.cpp
 * @brief Tests unitaires pour la classe Human
 * @version 0.1
 * @date 2026-01-27
 * @copyright Copyright (c) 2026
 */

#include <iostream>
#include <vector>
#include "Board.hpp"
#include "Human.hpp"

void test_human_movement() {
    Board b;
    cursor_t cur = {0, 0};
    Human h("Joueur1", {COLOR::RED});

    // Simuler ARROW_DOWN (nécessite de mocker l'Input ou de tester manuellement)
    h.playTurn(&b, &cur); 
    // Assert : cur.x doit être 1 si ARROW_DOWN a été pressé.
}

void test_stock_depletion() {
    Player p("Test", {COLOR::RED});
    // On utilise 3 pions SMALL
    p.usePion(COLOR::RED, SIZE::SMALL);
    p.usePion(COLOR::RED, SIZE::SMALL);
    p.usePion(COLOR::RED, SIZE::SMALL);

    if (!p.hasPion(COLOR::RED, SIZE::SMALL)) {
        std::cout << "SUCCESS: Stock SMALL épuisé correctement." << std::endl;
    }
}

/**
 * @file testHuman.cpp
 * @brief Tests unitaires pour la classe Human
 * @version 0.1
 * @date 2026-01-27
 * @copyright Copyright (c) 2026
 */

#include <iostream>
#include <cassert>
#include <vector>
#include "Human.hpp"
#include "Board.hpp"

void testHumanConstruction()
{
    std::cout << "Test: Construction du joueur humain..." << std::endl;
    
    std::vector<COLOR> colors = {RED, BLUE};
    Human human("Alice", colors);
    
    // Vérifier le nom
    assert(human.getName() == "Alice");
    
    // Vérifier que les couleurs sont bien assignées
    assert(human.getColor().size() == 2);
    assert(human.getColor()[0] == RED);
    
    std::cout << "✓ Construction du joueur réussie" << std::endl;
}

void testHumanStock()
{
    std::cout << "Test: Gestion du stock de pions..." << std::endl;
    
    std::vector<COLOR> colors = {GREEN};
    Human human("Bob", colors);
    
    // Au début, il doit avoir des pions MEDIUM de sa couleur
    assert(human.hasPion(GREEN, MEDIUM) == true);
    
    // On simule l'utilisation de ses 3 pions MEDIUM (selon ton Player.cpp)
    human.usePion(GREEN, MEDIUM);
    human.usePion(GREEN, MEDIUM);
    human.usePion(GREEN, MEDIUM);
    
    // Après 3 utilisations, il ne doit plus en avoir
    assert(human.hasPion(GREEN, MEDIUM) == false);
    
    // Mais il doit encore avoir des SMALL
    assert(human.hasPion(GREEN, SMALL) == true);
    
    std::cout << "✓ Gestion du stock réussie" << std::endl;
}

void testHumanPlayTurnMove()
{
    std::cout << "Test: Simulation d'un tour (Déplacement)..." << std::endl;
    
    Board board;
    std::vector<COLOR> colors = {YELLOW};
    Human human("Charlie", colors);
    
    cursor_t cursor = {1, 1}; // Position centrale initiale
    
    std::cout << "Note: Ce test attend une entree clavier (fleche ou entree)." << std::endl;
    
    // On appelle playTurn. 
    // Attention : l'appel est bloquant car il attend waitCtrlKey()
    playerAction_t action = human.playTurn(&board, &cursor);
    
    // Si l'utilisateur appuie sur une flèche, l'action doit être ARROW
    // Si l'utilisateur appuie sur Entrée, l'action doit être ENDPLAY (si case libre)
    assert(action == ARROW || action == ENDPLAY || action == PION_SEL_DISABLE);
    
    std::cout << "✓ Interaction playTurn testee" << std::endl;
}

void testHuman()
{
    std::cout << "\n========== TESTS HUMAN ==========" << std::endl;
    
    try {
        testHumanConstruction();
        testHumanStock();
        testHumanPlayTurnMove(); // Optionnel : peut être mis en commentaire pour des tests automatiques sans clavier
        
        std::cout << "\n✓ Tous les tests de la classe Human sont passés!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "\n✗ Erreur lors des tests: " << e.what() << std::endl;
    }
}