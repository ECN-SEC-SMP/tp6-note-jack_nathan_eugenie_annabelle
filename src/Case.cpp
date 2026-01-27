#include "Case.hpp"

Case::Case()
 : x(0), y(0)
{}

Case::Case(int x, int y)
    : x(x) , y(y)
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

Pion Case::getPion(SIZE s)
{
    switch (p->taille)
    {
    case SMALL:
        return pion[0];
        break;
    case MEDIUM:
        return pion[1];
        break;
    case LARGE:
        return pion[2];
        break;
    default:
        break;
    }
}


int Case::getX()
{
    return x;
}

int Case::getY()
{
    return y;
}

