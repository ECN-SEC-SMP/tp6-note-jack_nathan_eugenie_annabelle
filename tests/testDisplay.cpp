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

#include <iostream>
#include <exception>
#include <signal.h>
#include <stdlib.h>

bool running = true;

Display* disp = nullptr;


void sighandler(int sig)
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
    disp->printPionSelection(true);
    disp->print();

    while (running);
    
    delete disp;

    return;
}