#include "Board.hpp"

#include <string>

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
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            for (int s = 0; s < 3; s++)
            {
                Pion* p = this->cases[i][j].getPion((SIZE)s);
                if (p != nullptr) {
                    free(p);
                }
            }
        }
        
    }
}

Case* Board::getCase(int x, int y)
{
    return &cases[x][y];
}