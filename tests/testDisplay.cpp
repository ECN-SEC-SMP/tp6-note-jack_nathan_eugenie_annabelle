/**
 * @file testDisplay.cpp
 * @author Nathan
 * @brief 
 * @version 0.1
 * @date 2026-01-20
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include "tests.hpp"

#include "Display.hpp"
#include "Input.hpp"

#include <iostream>
#include <exception>
#include <signal.h>
#include <stdlib.h>
#include <assert.h>

static bool running = true;

static Display* disp = nullptr;
static Input* input = nullptr;


static void sighandler(int sig)
{
    running = false;

}

void testDisplay(void) {

    signal(SIGABRT, &sighandler);
	signal(SIGTERM, &sighandler);
	signal(SIGINT, &sighandler);

    disp = new Display();

    disp->setCursor(2, 2);
    disp->setCursor(MEDIUM);
    // disp->printPionSelection(true);
    disp->print();

    while (running);
    
    delete disp;

    return;
}

void testDisplayAsk(void) {
    uint8_t val;
    
    signal(SIGABRT, &sighandler);
	signal(SIGTERM, &sighandler);
	signal(SIGINT, &sighandler);

    disp = new Display();

    val = disp->getNbPlayers(1, 4);
    std::cout << "Nb Player is : " << val << "\n";
    
    val = disp->getNbRobot(0, 3);
    std::cout << "Nb Robot is : " << val << "\n";

    std::string ans = disp->getString("Did you had a greet day ?");
    std::cout << "Answer : " << ans << "\n";

    char tmp[2];
    std::cin >> tmp;

    delete disp;

    return;
}

void testDisplayInput(void) {
    signal(SIGABRT, &sighandler);
	signal(SIGTERM, &sighandler);
	signal(SIGINT, &sighandler);

    disp = new Display();

    input = Input::GetInstance();
    assert(input != nullptr);

    disp->setCursor(DISPLAY_SELECT_NONE, DISPLAY_SELECT_NONE);
    disp->setCursor(SMALL);
    // disp->printPionSelection(true);

    bool modePionSel = true;
    InputKey_t key = KEY_NONE;

    uint8_t x, y;
    enum SIZE sizeSel = SMALL;

    input->begin();

    disp->print();
    while (running) {

        key = input->waitCtrlKey();

        // ===== Exit
        if (key == KEY_SUPPR) {
            break;
        }
        
        // ===== Change mode
        if (key == KEY_SPACE) {
            modePionSel = !modePionSel;
        }

        if (!modePionSel) {
            // ===== Case selection
            disp->printPionSelection(false, 0, 0, 0);

            if (key == ARROW_UP) {
                if (x > 0) {
                    x--;
                }
            }
            if (key == ARROW_DOWN) {
                if (x < 2) {
                    x++;
                }
            }
            if (key == ARROW_RIGHT) {
                if (y < 2) {
                    y++;
                }
            }
            if (key == ARROW_LEFT) {
                if (y > 0) {
                    y--;
                }
            }
    
            disp->setCursor(x, y);
            disp->print();
        } else {
            // ===== Pion selection
            disp->printPionSelection(true, 1, 2, 3);

            if (key == ARROW_RIGHT) {
                if (sizeSel < LARGE) {
                    sizeSel = (enum SIZE)(sizeSel + 1);
                }
            }
            if (key == ARROW_LEFT) {
                if (sizeSel > SMALL) {
                    sizeSel = (enum SIZE)(sizeSel - 1);
                }
            }

            disp->setCursor(sizeSel);
            disp->print();
        }

        std::cout << "Got key ";
        if (key == ARROW_UP) { std::cout << "UP" << "\n";}
        if (key == ARROW_DOWN) { std::cout << "DOWN" << "\n";}
        if (key == ARROW_RIGHT) { std::cout << "RIGHT" << "\n";}
        if (key == ARROW_LEFT) { std::cout << "LEFT" << "\n";}
        if (key == KEY_SPACE) { std::cout << "SPACE" << "\n";}
        if (key == KEY_ENTER) { std::cout << "ENTER" << "\n";}
    }

    input->end();
    
    delete disp;

    return;
}