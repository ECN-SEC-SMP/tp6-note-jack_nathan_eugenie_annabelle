#include "Case.hpp"

Case::Case(int x, int y)
    : x:x ; y:y
{
    for (int i = 0; i < 3; i++)
    {
        pion[i] = nullptr;
    }
}

Case::~Case()
{
    for (int i = 0; i < 3; i++)
    {
        if (pion[i] != nullptr)
        {
            delete pion[i];
        }
    }
}

void Case::addPion(Pion* p){
    switch (p->taille)
    {
    case SMALL:
        pion[0] = p;
        break;
    case MEDIUM:
        pion[1] = p;
        break;
    case LARGE:
        pion[2] = p;
        break;
    default:
        break;
    }
}

void Case::deletePion(SIZE s)
{
    for(int i = 0; i < 3; i++) {
        if(pion[i]->taille == s)
        {
            delete pion[i];
        }
    }
}


int Case::getX()
{
    return position[0];
}

int Case::getY()
{
    return position[1];
}

