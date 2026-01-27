#include "Case.hpp"

Case::Case(int x, int y)
    : position{x, y}
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

void Case::deletePion()
{
    
}
