#pragma once

#include "Pion.hpp"
#include "Size.hpp"

class Case
{
private:
    Pion* pion[3];
    int x;
    int y;
public:
    Case(int x, int y);
    ~Case();
    void addPion(Pion* p);
    void deletePion(SIZE s);
    int getX();
    int getY();
};
