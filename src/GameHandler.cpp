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
    this->setup();
}

GameHandler::~GameHandler()
{
}

bool GameHandler::detectWin(Case *box)
{
    bool res = false;

    // res = this->checkDiagL(box);
    // if (!res)
    // {
    //     res = this->checkDiagR(box);
    // }
    // if (!res)
    // {
    //     res = this->checkLineHB(box);
    // }

    // if (!res)
    // {
    //     res = this->checkLineLR(box);
    // }

    // if (!res)
    // {
    //     res = this->checkCase(box);
    // }

    return res;
}

bool GameHandler::checkDiagL(int x, int y)
{
    // int x = box->x;
    // int y = box->y;

    if (x != y)
    {
        return false;
    }

    // Comparer 0,0 && 1,1 && 2,2
    return true;
}
bool GameHandler::checkDiagR(int x, int y)
{

    if ((x == 2 && y == 0) || (x == 1 && y == 1) || (x == 0 && y == 2))
    {
        return false;
    }
    // Comparer 2,0 && 1,1 && 0,2

    return true;
}
bool GameHandler::checkLineHB(int x, int y)
{

    // comparer x, 0 && x, 1 && x, 2

    return true;
}
bool GameHandler::checkLineLR(int x, int y)
{
    // comparer 0, y && 1, y && 2, y
    return true;
}
bool GameHandler::checkCase(int x, int y)
{
    // Comparer la case
    return true;
}

COLOR GameHandler::getRandomColor()
{
    std::vector<COLOR> colors = {COLOR::BLUE, COLOR::GREEN, COLOR::RED, COLOR::YELLOW};

    std::vector<COLOR> takenColor = {};

    for (Player *p : this->players)
    {
        const std::vector<COLOR> &pColor = p->getColor();
        for (size_t i = 0; i < pColor.size(); i++)
        {
            takenColor.push_back(pColor.at(0));
        }
    }

    srand(time(0));
    bool newColor;
    int randomNum;
    do
    {
        newColor = true;
        randomNum = rand() % 4;

        for (COLOR c : takenColor)
        {
            if (c == colors.at(randomNum))
            {
                newColor = false;
            }
        }

    } while (!newColor);

    // Generate a random number between 0 and 3

    return colors[randomNum];
}