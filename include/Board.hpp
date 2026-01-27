#include "Case.hpp"

#define BOARD_SIZE 3

class Board
{
private:
    Case cases[BOARD_SIZE][BOARD_SIZE];
public:
    Board();
    ~Board();
    Case getCase(int x, int y);
};
