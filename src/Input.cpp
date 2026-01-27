/**
 * @file Input.cpp
 * @brief
 * @version 0.1
 * @date 2026-01-27
 *
 * @copyright Copyright (c) 2026
 *
 */
/* Includes ---------------------------------------------------------------- */
#include "Input.hpp"

#include <unistd.h>
#include <termios.h>
#include <string>
#include <iostream>

/* Private variables ------------------------------------------------------- */

static termios oldTerminal;

/* Private declaration ----------------------------------------------------- */

int16_t getcharAlt(void);

/* Private methods --------------------------------------------------------- */

int16_t getcharAlt(void)
{
    int16_t buff[2];
    int l = read(STDIN_FILENO, buff, 1);
    if (l > 0)
    {
        return buff[0];
    }
    return (EOF);
}

/* Public methods ---------------------------------------------------------- */

Input *Input::input_ = nullptr;

Input::Input(void)
{
}

Input::~Input(void)
{
    if (input_ != nullptr)
    {
        delete input_;
    }
}

Input *Input::GetInstance(void)
{
    /**
     * This is a safer way to create an instance. instance = new Singleton is
     * dangeruous in case two instance threads wants to access at the same time
     */
    if (input_ == nullptr)
    {
        input_ = new Input();
    }
    return input_;
}

void Input::begin(void)
{
    termios newt;

    tcgetattr(STDIN_FILENO, &oldTerminal); // Sauvegarde de l'ancien mode
    newt = oldTerminal;
    newt.c_lflag &= ~(ICANON | ECHO); // Mode sans buffer ni echo
    newt.c_cc[VMIN] = 0;
    newt.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Activation du mode
}

void Input::end(void)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &oldTerminal);
}

char Input::waitForKey(void)
{

    int16_t c;
    do
    {
        usleep(30000); // Sleep 30 ms
        c = getcharAlt();
    } while (c == EOF);

    return c;
}

InputKey_t Input::waitCtrlKey(void)
{

    InputKey_t ret = KEY_NONE;
    char c;

    do
    {

        c = this->waitForKey();

        if (KEY_VAL_ENTER == c)
        {
            ret = KEY_ENTER;
        }
        else if (KEY_VAL_SPACE == c)
        {
            ret = KEY_SPACE;
        }
        else if (KEY_VAL_SUPPR == c)
        {
            ret = KEY_SUPPR;
        }
        else if (KEY_VAL_ARROW_START1 == c)
        {

            c = this->waitForKey();
            if (KEY_VAL_ARROW_START2 == c)
            {

                c = this->waitForKey();
                if (KEY_VAL_ARROW_UP == c)
                {
                    ret = ARROW_UP;
                }
                else if (KEY_VAL_ARROW_RIGHT == c)
                {
                    ret = ARROW_RIGHT;
                }
                else if (KEY_VAL_ARROW_DOWN == c)
                {
                    ret = ARROW_DOWN;
                }
                else if (KEY_VAL_ARROW_LEFT == c)
                {
                    ret = ARROW_LEFT;
                }
            }
        }

    } while (ret == KEY_NONE);

    return ret;
}