/**
 * @file Display.cpp
 * @author Nathan
 * @brief 
 * @version 0.1
 * @date 2026-01-20
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "Display.hpp"

#include <exception>
#include <format>
#include <iostream>

// Lines
#define LINE_HORIZ  "──"               // Vertical grid line x3 for case printing
#define LINE_HORIZ_WALL  "══"          // Vertical wall line x3 for case printing
#define CROSSING_LINE_HORIZ_WALL  "═"   // Vertical wall line
#define LINE_VERTI  "│"                 // Horizontal grid line
#define LINE_VERTI_WALL  "║"            // Horizontal wall line
#define CROSSING_LINE_VERTI_WALL  "║"   // Horizontal wall line
#define SPACE       "  "               // Empty space for case

// Corners
#define CORNER_TOPLEFT  "┌"             // Top left corner grid
#define CORNER_TOPLEFT_WALL_FULL    "╔" // Top left corner wall
#define CORNER_TOPLEFT_WALL_BOT     "╓" // Top left corner bottom wall
#define CORNER_TOPLEFT_WALL_RIGHT   "╒" // Top left corner right wall

#define CORNER_TOPRIGHT "┐"             // Top right corner grid
#define CORNER_TOPRIGHT_WALL_FULL   "╗" // Top right corner wall
#define CORNER_TOPRIGHT_WALL_BOT    "╖" // Top right corner bottom wall
#define CORNER_TOPRIGHT_WALL_LEFT   "╕" // Top right corner left wall

#define CORNER_BOTLEFT  "└"             // Bottom left corner grid
#define CORNER_BOTLEFT_WALL_FULL    "╚" // Bottom left corner wall
#define CORNER_BOTLEFT_WALL_TOP     "╙" // Bottom left corner top wall
#define CORNER_BOTLEFT_WALL_RIGHT   "╘" // Bottom left corner right wall

#define CORNER_BOTRIGHT "┘"             // Bottom right corner grid
#define CORNER_BOTRIGHT_WALL_FULL   "╝" // Bottom right corner wall
#define CORNER_BOTRIGHT_WALL_TOP    "╜" // Bottom right corner top wall
#define CORNER_BOTRIGHT_WALL_LEFT   "╛" // Bottom right corner left wall

// Intersections
#define CROSSING_VERTI_TO_RIGHT "├"             // Vertical grid with extension to the right
#define CROSSING_VERTI_TO_RIGHT_WALL_FULL   "╠" // Vertical wall with extension to the right
#define CROSSING_VERTI_TO_RIGHT_WALL_RIGHT  "╞" // Vertical grid with wall extension to the right
#define CROSSING_VERTI_TO_RIGHT_WALL_VERTI  "╟" // Vertical wall with grid extension to the right

#define CROSSING_VERTI_TO_LEFT  "┤"             // Vertical grid with extension to the left
#define CROSSING_VERTI_TO_LEFT_WALL_FULL    "╣" // Vertical wall with extension to the left
#define CROSSING_VERTI_TO_LEFT_WALL_LEFT    "╡" // Vertical grid with wall extension to the left
#define CROSSING_VERTI_TO_LEFT_WALL_VERTI   "╢" // Vertical wall with grid extension to the left

#define CROSSING_HORIZ_TO_TOP   "┴"             // Horizontal grid with extension at the top
#define CROSSING_HORIZ_TO_TOP_WALL_FULL     "╩" // Horizontal wall with extension at the top
#define CROSSING_HORIZ_TO_TOP_WALL_TOP      "╨" // Horizontal grid with wall extension at the top
#define CROSSING_HORIZ_TO_TOP_WALL_HORIZ    "╧" // Horizontal wall with grid extension at the top

#define CROSSING_HORIZ_TO_BOT   "┬"             // Horizontal grid with extension at the bottom
#define CROSSING_HORIZ_TO_BOT_WALL_FULL     "╦" // Horizontal wall with extension at the bottom
#define CROSSING_HORIZ_TO_BOT_WALL_BOT      "╥" // Horizontal grid with wall extension at the bottom
#define CROSSING_HORIZ_TO_BOT_WALL_HORIZ    "╤" // Horizontal wall with grid extension at the bottom

#define CROSSING_CROSS          "┼"             // Crossing grid
#define CROSSING_CROSS_WALL_FULL            "╬" // Crossing wall
#define CROSSING_CROSS_WALL_VERTI           "╫" // Crossing with vertical wall
#define CROSSING_CROSS_WALL_HORIZ           "╪" // Crossing with horizontal wall

#define CIRCLE_PIXEL    "██"

// Ansi Escapes Codes
// ESC Code Sequence 	Description
// ESC[38;5;{ID}m 	    Set foreground color.
// ESC[48;5;{ID}m 	    Set background color.

#define ANSI_CODE_ERASE "\33[0J"                        // ANSI ESCAPE CODE TO erase terminal
#define ANSI_CODE_CURSOR_RESET "\33[H"                  // ANSI ESCAPE CODE TO put cursor at x : 0, y : 0
#define ANSI_CODE_BACKGROUND_RESET "\033[39m\033[49m"   // ANSI ESCAPE CODE TO reset background color to default

#define ANSI_CODE_BACKGROUND_APP "\33[48;5;15m"         // ANSI ESCAPE CODE TO set the app background white
#define ANSI_CODE_BACKGROUND_CENTER "\33[48;5;0m"       // ANSI ESCAPE CODE TO set the app background black
#define ANSI_CODE_FOREGROUND_APP "\33[38;5;0m"          // ANSI ESCAPE CODE TO set the app foreground black
#define ANSI_CODE_FOREGROUND_CENTER "\33[38;5;15m"      // ANSI ESCAPE CODE TO set the app foreground white

#define ANSI_CODE_FOREGROUND_RED "\33[38;5;1m"
#define ANSI_CODE_FOREGROUND_BLUE "\33[38;5;4m"
#define ANSI_CODE_FOREGROUND_GREEN "\33[38;5;2m"
#define ANSI_CODE_FOREGROUND_YELLOW "\33[38;5;220m"

#define ANSI_CODE_LINE_COLOR "\33[38;5;253m"            // ANSI ESCAPE CODE TO set color for grid lines in grey
#define ANSI_CODE_WALL_COLOR "\33[38;5;0m"              // ANSI ESCAPE CODE TO set color for wall in black

#define ANSI_CODE_SELECT_COLOR ANSI_CODE_WALL_COLOR

#define ANSI_CODE_ERASE_LINE "\33[K"                    // ANSI ESCAPE CODE TO erase a line

#define ANSI_CODE_CURSOR_POS_SET   "\33["             // ANSI ESCAPE CODE TO load a saved cursor position
#define ANSI_CODE_CURSOR_POS_SAVE   "\33[s"             // ANSI ESCAPE CODE TO save cursor position
#define ANSI_CODE_CURSOR_POS_LOAD   "\33[u"             // ANSI ESCAPE CODE TO load a saved cursor position

/* Globals ----------------------------------------------------------------- */

#define PION_SEL_HARDCODE_NB_LINES 7
const std::string PION_SEL_HARDCODE_SMALL[PION_SEL_HARDCODE_NB_LINES] = {
    "╔══ %d/3  ══╗── %d/3  ──┬── %d/3  ──┐",
    "║          ║          │██████████│",
    "              ██████   ██      ██ ",
    "     ██       ██  ██   ██      ██ ",
    "              ██████   ██      ██ ",
    "║          ║          │██████████│",
    "╚══      ══╝──      ──┴──      ──┘",
};

const std::string PION_SEL_HARDCODE_MEDIUM[PION_SEL_HARDCODE_NB_LINES] = {
    "┌── %d/3  ──╔══ %d/3  ══╗── %d/3  ──┐",
    "│          ║          ║██████████│",
    "              ██████   ██      ██ ",
    "     ██       ██  ██   ██      ██ ",
    "              ██████   ██      ██ ",
    "│          ║          ║██████████│",
    "└──      ──╚══      ══╝──      ──┘",
};

const std::string PION_SEL_HARDCODE_LARGE[PION_SEL_HARDCODE_NB_LINES] = {
    "┌── %d/3  ──┬── %d/3  ──╔══ %d/3  ══╗",
    "│          │          ║██████████║",
    "              ██████   ██      ██ ",
    "     ██       ██  ██   ██      ██ ",
    "              ██████   ██      ██ ",
    "│          │          ║██████████║",
    "└──      ──┴──      ──╚══      ══╝",
};

/* Private methods --------------------------------------------------------- */

void Display::loadGrille(void)
{
    std::string to_put;

    constexpr uint8_t ROW_MODULO = CANVAS_CASE_SIZE + 1;
    
    for (uint8_t i = 0; i < CANVAS_SIZE; i++) {
        for (uint8_t j = 0; j < CANVAS_SIZE; j++) {
            // Corners
            if ((i == 0) && (j == 0)) {
                to_put = CORNER_TOPLEFT;
            }
            else if ((i == 0) && (j == (CANVAS_SIZE - 1))) {
                to_put = CORNER_TOPRIGHT;
            }
            else if ((i == (CANVAS_SIZE - 1)) && (j == 0)) {
                to_put = CORNER_BOTLEFT;
            }
            else if ((i == (CANVAS_SIZE - 1)) && (j == (CANVAS_SIZE - 1))) {
                to_put = CORNER_BOTRIGHT;
            }
            
            // // Crossing
            else if ((i == 0 )&& !(j % ROW_MODULO)) {
                to_put = CROSSING_HORIZ_TO_BOT;
            }
            else if ((i == (CANVAS_SIZE - 1)) && !(j % ROW_MODULO)) {
                to_put = CROSSING_HORIZ_TO_TOP;
            }
            else if (!(i % ROW_MODULO) && (j == 0)) {
                to_put = CROSSING_VERTI_TO_RIGHT;
            }
            else if (!(i % ROW_MODULO) && (j == (CANVAS_SIZE - 1))) {
                to_put = CROSSING_VERTI_TO_LEFT;
            }
            else if (!(i % ROW_MODULO) && !(j % ROW_MODULO)) {
                to_put = CROSSING_CROSS;
            }
            
            // Lines
            else if (!(i % ROW_MODULO)) {
                to_put = LINE_HORIZ;
            }
            else if (!(j % ROW_MODULO)) {
                to_put = LINE_VERTI;
            }
            else {
                to_put = SPACE;
            }
            
            this->printBuff[i][j] = to_put;
        }
    }
}

void Display::loadCase(void)
{
    constexpr uint8_t STEP = CANVAS_CASE_SIZE + CANVAS_WALL_SIZE;

    // TODO : Finish when board class is implemented

    for (uint8_t i = 0; i < NB_COL; i++)
    {
        for (uint8_t j = 0; j < NB_ROW; j++)
        {
            // Print Board       
            if (1 /*Cas as large*/) {
                // this->loadCircleLarge(STEP * i + 1, STEP * j + 1, color);
            }     
            if (1 /*Cas as medium*/) {
                // this->loadCircleMedium(STEP * i + 1, STEP * j + 1, color);
            }     
            if (1 /*Cas as small*/) {
                // this->loadCircleSmall(STEP * i + 1, STEP * j + 1, color);
            }     
        }
    }

    // Print Large
    this->loadCircleLarge(1, 1, ANSI_CODE_FOREGROUND_YELLOW);
    this->loadCircleLarge(1, 7, ANSI_CODE_FOREGROUND_BLUE);
    this->loadCircleLarge(7, 7, ANSI_CODE_FOREGROUND_RED);
    this->loadCircleLarge(13, 13, ANSI_CODE_FOREGROUND_GREEN);
    
    // Print Medium
    this->loadCircleMedium(1, 1, ANSI_CODE_FOREGROUND_GREEN);
    
    this->loadCircleSmall(1, 1, ANSI_CODE_FOREGROUND_BLUE);

}

void Display::loadCircleSmall(uint8_t topLefCornerX, uint8_t topLefCornerY, std::string colorCode)
{    

    this->printBuff[topLefCornerX + 2][topLefCornerY + 2] = colorCode + CIRCLE_PIXEL + ANSI_CODE_FOREGROUND_APP;

    return;
}

void Display::loadCircleMedium(uint8_t topLefCornerX, uint8_t topLefCornerY, std::string colorCode)
{
    this->printBuff[topLefCornerX + 1][topLefCornerY + 1] = colorCode + CIRCLE_PIXEL + ANSI_CODE_FOREGROUND_APP;
    this->printBuff[topLefCornerX + 1][topLefCornerY + 2] = colorCode + CIRCLE_PIXEL + ANSI_CODE_FOREGROUND_APP;
    this->printBuff[topLefCornerX + 1][topLefCornerY + 3] = colorCode + CIRCLE_PIXEL + ANSI_CODE_FOREGROUND_APP;
  
    this->printBuff[topLefCornerX + 2][topLefCornerY + 1] = colorCode + CIRCLE_PIXEL + ANSI_CODE_FOREGROUND_APP;
    this->printBuff[topLefCornerX + 2][topLefCornerY + 3] = colorCode + CIRCLE_PIXEL + ANSI_CODE_FOREGROUND_APP;
    
    this->printBuff[topLefCornerX + 3][topLefCornerY + 1] = colorCode + CIRCLE_PIXEL + ANSI_CODE_FOREGROUND_APP;
    this->printBuff[topLefCornerX + 3][topLefCornerY + 2] = colorCode + CIRCLE_PIXEL + ANSI_CODE_FOREGROUND_APP;
    this->printBuff[topLefCornerX + 3][topLefCornerY + 3] = colorCode + CIRCLE_PIXEL + ANSI_CODE_FOREGROUND_APP;

    return;
}

void Display::loadCircleLarge(uint8_t topLefCornerX, uint8_t topLefCornerY, std::string colorCode)
{
    this->printBuff[topLefCornerX + 0][topLefCornerY + 0] = colorCode + CIRCLE_PIXEL + ANSI_CODE_FOREGROUND_APP;
    this->printBuff[topLefCornerX + 0][topLefCornerY + 1] = colorCode + CIRCLE_PIXEL + ANSI_CODE_FOREGROUND_APP;
    this->printBuff[topLefCornerX + 0][topLefCornerY + 2] = colorCode + CIRCLE_PIXEL + ANSI_CODE_FOREGROUND_APP;
    this->printBuff[topLefCornerX + 0][topLefCornerY + 3] = colorCode + CIRCLE_PIXEL + ANSI_CODE_FOREGROUND_APP;
    this->printBuff[topLefCornerX + 0][topLefCornerY + 4] = colorCode + CIRCLE_PIXEL + ANSI_CODE_FOREGROUND_APP;
    
    this->printBuff[topLefCornerX + 1][topLefCornerY + 0] = colorCode + CIRCLE_PIXEL + ANSI_CODE_FOREGROUND_APP;
    this->printBuff[topLefCornerX + 2][topLefCornerY + 0] = colorCode + CIRCLE_PIXEL + ANSI_CODE_FOREGROUND_APP;
    this->printBuff[topLefCornerX + 3][topLefCornerY + 0] = colorCode + CIRCLE_PIXEL + ANSI_CODE_FOREGROUND_APP;
    this->printBuff[topLefCornerX + 4][topLefCornerY + 0] = colorCode + CIRCLE_PIXEL + ANSI_CODE_FOREGROUND_APP;
    
    this->printBuff[topLefCornerX + 1][topLefCornerY + 4] = colorCode + CIRCLE_PIXEL + ANSI_CODE_FOREGROUND_APP;
    this->printBuff[topLefCornerX + 2][topLefCornerY + 4] = colorCode + CIRCLE_PIXEL + ANSI_CODE_FOREGROUND_APP;
    this->printBuff[topLefCornerX + 3][topLefCornerY + 4] = colorCode + CIRCLE_PIXEL + ANSI_CODE_FOREGROUND_APP;
    this->printBuff[topLefCornerX + 4][topLefCornerY + 4] = colorCode + CIRCLE_PIXEL + ANSI_CODE_FOREGROUND_APP;
    
    this->printBuff[topLefCornerX + 4][topLefCornerY + 1] = colorCode + CIRCLE_PIXEL + ANSI_CODE_FOREGROUND_APP;
    this->printBuff[topLefCornerX + 4][topLefCornerY + 2] = colorCode + CIRCLE_PIXEL + ANSI_CODE_FOREGROUND_APP;
    this->printBuff[topLefCornerX + 4][topLefCornerY + 3] = colorCode + CIRCLE_PIXEL + ANSI_CODE_FOREGROUND_APP;    

    return;
}

void Display::loadSelectedCase(void) {
    std::string colorCode = std::string(ANSI_CODE_SELECT_COLOR);

    // Return if DISPLAY_SELECT_NONE
    if (this->selx < 0 || this->sely < 0) {
        return;
    }

    uint8_t topLefCornerX = this->selx * (CANVAS_CASE_SIZE + CANVAS_WALL_SIZE);
    uint8_t topLefCornerY = this->sely * (CANVAS_CASE_SIZE + CANVAS_WALL_SIZE);

    // Top left
    this->printBuff[topLefCornerX + 0][topLefCornerY + 0] = colorCode + CORNER_TOPLEFT_WALL_FULL + ANSI_CODE_FOREGROUND_APP;
    this->printBuff[topLefCornerX + 0][topLefCornerY + 1] = colorCode + LINE_HORIZ_WALL + ANSI_CODE_FOREGROUND_APP;
    this->printBuff[topLefCornerX + 1][topLefCornerY + 0] = colorCode + LINE_VERTI_WALL + ANSI_CODE_FOREGROUND_APP;
    
    // Bot left
    this->printBuff[topLefCornerX + 6][topLefCornerY + 0] = colorCode + CORNER_BOTLEFT_WALL_FULL + ANSI_CODE_FOREGROUND_APP;
    this->printBuff[topLefCornerX + 6][topLefCornerY + 1] = colorCode + LINE_HORIZ_WALL + ANSI_CODE_FOREGROUND_APP;
    this->printBuff[topLefCornerX + 5][topLefCornerY + 0] = colorCode + LINE_VERTI_WALL + ANSI_CODE_FOREGROUND_APP;
    
    // Top Right
    this->printBuff[topLefCornerX + 0][topLefCornerY + 6] = colorCode + CORNER_TOPRIGHT_WALL_FULL + ANSI_CODE_FOREGROUND_APP;
    this->printBuff[topLefCornerX + 0][topLefCornerY + 5] = colorCode + LINE_HORIZ_WALL + ANSI_CODE_FOREGROUND_APP;
    this->printBuff[topLefCornerX + 1][topLefCornerY + 6] = colorCode + LINE_VERTI_WALL + ANSI_CODE_FOREGROUND_APP;
    
    // Bot Right
    this->printBuff[topLefCornerX + 6][topLefCornerY + 6] = colorCode + CORNER_BOTRIGHT_WALL_FULL + ANSI_CODE_FOREGROUND_APP;
    this->printBuff[topLefCornerX + 6][topLefCornerY + 5] = colorCode + LINE_HORIZ_WALL + ANSI_CODE_FOREGROUND_APP;
    this->printBuff[topLefCornerX + 5][topLefCornerY + 6] = colorCode + LINE_VERTI_WALL + ANSI_CODE_FOREGROUND_APP;

}

void Display::loadSelectedPion(enum SIZE pionSize)
{
    

}

/* Public methods ---------------------------------------------------------- */

Display::Display(/* args */)
{
    this->selx = DISPLAY_SELECT_NONE;
    this->sely = DISPLAY_SELECT_NONE;

    this->pionSelEn = false;
    this->selPion = SMALL;

    std::cout << ANSI_CODE_BACKGROUND_APP;
    std::cout << ANSI_CODE_FOREGROUND_APP;
    std::cout << ANSI_CODE_CURSOR_RESET << ANSI_CODE_ERASE;
}

Display::~Display()
{
    std::cout << ANSI_CODE_BACKGROUND_RESET;
    std::cout << ANSI_CODE_CURSOR_RESET << ANSI_CODE_ERASE;
}

void Display::print(/* Board brd */)
{
    this->loadGrille();
    this->loadCase();
    this->loadSelectedCase();

    for (uint8_t i = 0; i < CANVAS_SIZE; i++)
    {
        for (uint8_t j = 0; j < CANVAS_SIZE; j++) {
            std::cout << this->printBuff[i][j];
        }
        std::cout << "\n";
    }

    if (!this->pionSelEn) {
        // Do not print pion selection
        return;
    }

    const std::string *pionSelBuff;

    if(this->selPion == LARGE) {
        pionSelBuff = PION_SEL_HARDCODE_LARGE;
    } else if (this->selPion == MEDIUM) {
        pionSelBuff = PION_SEL_HARDCODE_MEDIUM;
    } else {
        pionSelBuff = PION_SEL_HARDCODE_SMALL;
    }

    // First print with numbers
    char tempBuff[50];
    snprintf(tempBuff, 50, pionSelBuff[0].c_str(), this->smallNb, this->mediumNb, this->largeNb);
    std::cout << tempBuff << "\n";

    for (uint8_t i = 1; i < PION_SEL_HARDCODE_NB_LINES; i++)
    {
        std::cout << pionSelBuff[i] << "\n";
    }

    return;
}

void Display::printPionSelection(bool enable, uint8_t smallNb, uint8_t mediumNb, uint8_t largeNb)
{
    this->pionSelEn = enable;
    this->smallNb = smallNb;
    this->mediumNb = mediumNb;
    this->largeNb = largeNb;

    return;
}


void Display::setCursor(uint8_t x, uint8_t y)
{
    // TODO : Replace '3' with defines
    if (x > 3 && y > 3) {
        return;
    }

    this->selx = x;
    this->sely = y;

    return;
}

void Display::setCursor(enum SIZE size)
{
    this->selPion = size;
    return;
}


uint8_t Display::getNbPlayers(uint8_t min, uint8_t max)
{
    uint8_t nbJoueur = 0;

    if ((min > 9) || (max > 9)) {
        throw std::invalid_argument("Min and max must be a digit");
    }

    do
    {
        std::cout << "\nCombien de joueurs ? (" << unsigned(min) << " à " << unsigned(max) << ") : ";
        std::cin >> nbJoueur;
        std::cin.ignore();
    }
    while((nbJoueur < ('0' + min)) || nbJoueur > ('0' + max));
    

    return nbJoueur;
}


uint8_t Display::getNbRobot(uint8_t min, uint8_t max)
{
    uint8_t nbJoueur = 0;

    if ((min > 9) || (max > 9)) {
        throw std::invalid_argument("Min and max must be a digit");
    }

    do
    {
        std::cout << "\nCombien de robot ? (" << unsigned(min) << " à " << unsigned(max) << ") : ";
        std::cin >> nbJoueur;
        std::cin.ignore();
    }
    while((nbJoueur < ('0' + min)) || nbJoueur > ('0' + max));
    

    return nbJoueur;
}

std::string Display::getString(std::string question)
{
    std::string answer = "";

    std::cout << question;
    std::cin >> answer;

    return answer;
}