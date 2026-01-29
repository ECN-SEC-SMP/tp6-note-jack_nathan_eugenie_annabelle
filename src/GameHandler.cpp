#include "GameHandler.hpp"

GameHandler::GameHandler(void)
{
    this->players = {};
    this->board = new Board();
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

    int totalJoueurs = nbJoueurs + nbRobots;
    for (int i = 0; i < nbJoueurs; i++)
    {

        std::vector<COLOR> colors = {};
        if (totalJoueurs == 2)
        {
            colors.push_back(COLOR::BLUE);
        }
        colors.push_back(COLOR::GREEN);
        const std::string name = std::to_string(i);
        this->players.push_back(new Human(name, colors));
    }

    for (int i = 0; i < nbRobots; i++)
    {
        // this->players.push_back(new Robot(name, colors));

        // this.players.push(Robot());
    }

    std::cout << "Joueurs humains : " << nbJoueurs
              << " | Robots : " << nbRobots << std::endl;
}

void GameHandler::start(void)
{
    srand(time(0));

    this->setup();


}

GameHandler::~GameHandler()
{
}

COLOR GameHandler::getRandomColor()
{
    std::vector<COLOR> colors = {COLOR::BLUE, COLOR::GREEN, COLOR::RED, COLOR::YELLOW};

    std::vector<COLOR> takenColors = {};

    for (Player *p : this->players)
    {
        const std::vector<COLOR> &pColor = p->getColor();
        for (size_t i = 0; i < pColor.size(); i++)
        {
            takenColors.push_back(pColor.at(i));
        }
    }

    bool newColor;
    int randomNum;
    do
    {
        newColor = true;
        randomNum = rand() % 4;

        for (COLOR takenColor : takenColors)
        {
            if (takenColor == colors.at(randomNum))
            {
                newColor = false;
            }
        }

    } while (!newColor);

    // Generate a random number between 0 and 3

    return colors[randomNum];
}

bool GameHandler::has(int x, int y, SIZE s, COLOR c) const
{
    Case cell = board->getCase(x, y);
    Pion *p = cell.getPion(s);

    if (p == NULL)
    {
        return false;
    }
    if (p->Color != c)
    {
        return false;
    }
    return true;
}

bool GameHandler::checkStack(int x, int y, COLOR c) const
{

    if (!has(x, y, SMALL, c))
    {
        return false;
    }
    if (!has(x, y, MEDIUM, c))
    {
        return false;
    }
    if (!has(x, y, LARGE, c))
    {
        return false;
    }
    return true;
}

bool GameHandler::checkRow(int x, COLOR c) const
{
    // Condition 1 : 3 identiques (même taille)
    if (has(x, 0, SMALL, c) && has(x, 1, SMALL, c) && has(x, 2, SMALL, c))
    {
        return true;
    }
    if (has(x, 0, MEDIUM, c) && has(x, 1, MEDIUM, c) && has(x, 2, MEDIUM, c))
    {
        return true;
    }
    if (has(x, 0, LARGE, c) && has(x, 1, LARGE, c) && has(x, 2, LARGE, c))
    {
        return true;
    }

    // Condition 2 : croissant
    if (has(x, 0, SMALL, c) && has(x, 1, MEDIUM, c) && has(x, 2, LARGE, c))
    {
        return true;
    }

    // Condition 2 : décroissant
    if (has(x, 0, LARGE, c) && has(x, 1, MEDIUM, c) && has(x, 2, SMALL, c))
    {
        return true;
    }

    return false;
}

bool GameHandler::checkCol(int y, COLOR c) const
{
    // Condition 1 : 3 identiques
    if (has(0, y, SMALL, c) && has(1, y, SMALL, c) && has(2, y, SMALL, c))
    {
        return true;
    }
    if (has(0, y, MEDIUM, c) && has(1, y, MEDIUM, c) && has(2, y, MEDIUM, c))
    {
        return true;
    }
    if (has(0, y, LARGE, c) && has(1, y, LARGE, c) && has(2, y, LARGE, c))
    {
        return true;
    }

    // Condition 2 : croissant
    if (has(0, y, SMALL, c) && has(1, y, MEDIUM, c) && has(2, y, LARGE, c))
    {
        return true;
    }

    // Condition 2 : décroissant
    if (has(0, y, LARGE, c) && has(1, y, MEDIUM, c) && has(2, y, SMALL, c))
    {
        return true;
    }

    return false;
}

bool GameHandler::checkDiagMain(COLOR c) const
{
    // (0,0) (1,1) (2,2)

    // Condition 1 : 3 identiques
    if (has(0, 0, SMALL, c) && has(1, 1, SMALL, c) && has(2, 2, SMALL, c))
    {
        return true;
    }
    if (has(0, 0, MEDIUM, c) && has(1, 1, MEDIUM, c) && has(2, 2, MEDIUM, c))
    {
        return true;
    }
    if (has(0, 0, LARGE, c) && has(1, 1, LARGE, c) && has(2, 2, LARGE, c))
    {
        return true;
    }

    // Condition 2 : croissant
    if (has(0, 0, SMALL, c) && has(1, 1, MEDIUM, c) && has(2, 2, LARGE, c))
    {
        return true;
    }

    // Condition 2 : décroissant
    if (has(0, 0, LARGE, c) && has(1, 1, MEDIUM, c) && has(2, 2, SMALL, c))
    {
        return true;
    }

    return false;
}

bool GameHandler::checkDiagAnti(COLOR c) const
{
    // (0,2) (1,1) (2,0)

    // Condition 1 : 3 identiques
    if (has(0, 2, SMALL, c) && has(1, 1, SMALL, c) && has(2, 0, SMALL, c))
    {
        return true;
    }
    if (has(0, 2, MEDIUM, c) && has(1, 1, MEDIUM, c) && has(2, 0, MEDIUM, c))
    {
        return true;
    }
    if (has(0, 2, LARGE, c) && has(1, 1, LARGE, c) && has(2, 0, LARGE, c))
    {
        return true;
    }
    // Condition 2 : croissant
    if (has(0, 2, SMALL, c) && has(1, 1, MEDIUM, c) && has(2, 0, LARGE, c))
    {
        return true;
    }

    // Condition 2 : décroissant
    if (has(0, 2, LARGE, c) && has(1, 1, MEDIUM, c) && has(2, 0, SMALL, c))
    {
        return true;
    }

    return false;
}

bool GameHandler::detectWin(int x, int y, COLOR c) const
{
    // Empilement (condition 3)
    if (checkStack(x, y, c))
    {
        return true;
    }

    // Ligne + colonne
    if (checkRow(x, c))
    {
        return true;
    }
    if (checkCol(y, c))
    {
        return true;
    }

    // Diagonales seulement si on est dessus
    if (x == y)
    {
        if (checkDiagMain(c))
        {
            return true;
        }
    }

    if (x + y == 2)
    {
        if (checkDiagAnti(c))
        {
            return true;
        }
    }

    return false;
}
