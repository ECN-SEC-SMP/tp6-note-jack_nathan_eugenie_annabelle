#pragma once

#include "Pion.hpp"
#include "Size.hpp"

class Case
{
private:
    Pion* pion[3];
    int position[2]; // x et y
public:
    Case(int x, int y);
    ~Case();
    void deletePion(SIZE s);
    void addPion(Pion* p);
};
