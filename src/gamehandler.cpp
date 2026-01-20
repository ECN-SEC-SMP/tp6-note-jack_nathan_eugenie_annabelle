#include "gamehandler.hpp"

GameHandler::GameHandler(void)
{
    // this->players = [];
    // this->board = getBoard();
    this->currentPlayer = 0;
}

void GameHandler::setup()
{
    // Créer joueurs

    // Faire un choix entre 2 et 4
    std::cout << "Combien de joueurs " << std::endl;

    // Get valeur
    int nbJoueurs = 0;

    // Faire un choix entre 0 et nbJoueurs - 1
    std::cout << "Combien de robot ?" << std::endl;

    int nbRobots = 0;
    for (int i = 0; i < (nbJoueurs - nbRobots); i++)
    {
        // this->players.push(Humain())
    }

    for (int i = 0; i < (nbRobots); i++)
    {
        // this->players.push(Robot())
    }

}

void GameHandler::start(void)
{
    this->setup();
}

GameHandler::~GameHandler()
{
}