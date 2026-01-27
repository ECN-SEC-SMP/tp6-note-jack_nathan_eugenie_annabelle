#include "Case.hpp"

Case::Case() : x(0), y(0)
{
    for (int i = 0; i < 3; i++) pion[i] = nullptr;
}

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

void Case::addPion(Pion* p)
{
    int idx = -1;
    if (p->taille == SMALL) idx = 0;
    else if (p->taille == MEDIUM) idx = 1;
    else if (p->taille == LARGE) idx = 2;

    if (idx != -1) {
        delete pion[idx];     
        pion[idx] = p;
    }
}

void Case::deletePion(SIZE s)
{
    for (int i = 0; i < 3; i++) {
        if (pion[i] != nullptr && pion[i]->taille == s) {
            delete pion[i];
            pion[i] = nullptr;
        }
    }
}


Pion* Case::getPion(SIZE s)
{
    if (s == SMALL)  return pion[0];
    if (s == MEDIUM) return pion[1];
    if (s == LARGE)  return pion[2];
    return nullptr;
}


int Case::getX()
{
    return x;
}

int Case::getY()
{
    return y;
}

