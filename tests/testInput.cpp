/**
 * @file testInput.cpp
 * @brief 
 * @version 0.1
 * @date 2026-01-27
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#include "tests.hpp"

#include "Input.hpp"

#include <iostream>
#include <exception>
#include <signal.h>
#include <stdlib.h>
#include <assert.h>

static bool running = true;

static Input* input = nullptr;

static void sighandler(int sig)
{
    running = false;

}

void testInput(void) {

    signal(SIGABRT, &sighandler);
	signal(SIGTERM, &sighandler);
	signal(SIGINT, &sighandler);

    input = Input::GetInstance();
    assert(input != nullptr);

    input->begin();
    while (running) {
        int16_t c = input->waitForKey();
        std::cout << "c = " << std::hex << c << "\n";
        if (c == 'q') {
            break;
        }

        // InputKey_t key = input->waitCtrlKey();
        // std::cout << "Key : " << key << "\n";
        // if (key == KEY_ENTER) {
        //     break;
        // }
    }

    input->end();

    return;
}