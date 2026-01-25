#include "gamehandler.hpp"

GameHandler::GameHandler(void)
{
    // this->players = [];
    // this->board = getBoard();
    this->currentPlayer = 0;
}

void GameHandler::setup()
{
    std::cout << "-------------------------" << std::endl;
    std::cout << "| Bienvenue sur 0trio ! |" << std::endl;
    std::cout << "-------------------------" << std::endl;

    std::cout << "Combien de joueurs entre " << MIN_PLAYER
              << " et " << MAX_PLAYER << std::endl;

    int nbJoueurs = 0;
    int nbRobots = 0;

    // Saisie du nombre de joueurs
    do
    {
        std::cin >> nbJoueurs;
    } while (nbJoueurs < MIN_PLAYER || nbJoueurs > MAX_PLAYER);

    int maxRobots = MAX_PLAYER - nbJoueurs;

    // 1 seul joueur
    if (nbJoueurs == 1)
    {
        do
        {
            std::cout << "Combien de robots entre 1 et " << maxRobots << " ?" << std::endl;
            std::cin >> nbRobots;
        } while (nbRobots < 1 || nbRobots > maxRobots);
    }
    else if (nbJoueurs < MAX_PLAYER) // Plusieurs joueurs mais on peut ajouter des robots
    {
        char reponse;
        do
        {
            std::cout << "Souhaitez-vous ajouter des robots ? (y/n)" << std::endl;
            std::cin >> reponse;
        } while (reponse != 'y' && reponse != 'Y' &&
                 reponse != 'n' && reponse != 'N');

        if (reponse == 'y' || reponse == 'Y')
        {
            do
            {
                std::cout << "Combien de robots entre 1 et " << maxRobots << " ?" << std::endl;
                std::cin >> nbRobots;
            } while (nbRobots < 1 || nbRobots > maxRobots);
        }
    }

    for (int i = 0; i < nbJoueurs; i++)
    {
        // this.players.push(Humain());
    }
    for (int i = 0; i < nbRobots; i++)
    {
        // this.players.push(Robot());
    }

    std::cout << "Joueurs humains : " << nbJoueurs
              << " | Robots : " << nbRobots << std::endl;
}

void GameHandler::start(void)
{
    this->setup();
}

GameHandler::~GameHandler()
{
}

bool GameHandler::detectWin(/*Case* case*/) {
}
