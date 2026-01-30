#include "Board.hpp"

Board::Board(){
    for(int i = 0; i < 3; i++)
    {
        for(int y = 0; y < 3; y++)
        {
            this->cases[i][y] = Case(i, y);
        }
    }
}

Board::~Board(){
    
}

Case Board::getCase(int x, int y)
{
    return cases[x][y];
}

void Board::addPion(int x, int y, const Pion& p) // utilisé dans Bot.cpp
{
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) return;
    cases[x][y].addPion(new Pion(p));
}