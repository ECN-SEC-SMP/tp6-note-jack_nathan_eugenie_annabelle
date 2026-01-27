/**
 * @file Input.hpp
 * @brief 
 * @version 0.1
 * @date 2026-01-27
 * 
 * @copyright Copyright (c) 2026
 * 
 */
#ifndef INPUT_H_
#define INPUT_H_

#include <string>
#include <cstdint>

#define KEY_VAL_ARROW_START1    '\x1b'
#define KEY_VAL_ARROW_START2    '\x5b'
#define KEY_VAL_ARROW_UP        '\x41'
#define KEY_VAL_ARROW_DOWN      '\x42'
#define KEY_VAL_ARROW_RIGHT     '\x43'
#define KEY_VAL_ARROW_LEFT      '\x44'

#define KEY_VAL_ENTER   '\x0a'
#define KEY_VAL_SPACE   '\x20'
#define KEY_VAL_SUPPR   '\x7f'

typedef enum {
    KEY_NONE = 0,
    KEY_ENTER,
    KEY_SPACE,
    KEY_SUPPR,
    ARROW_UP,
    ARROW_RIGHT,
    ARROW_DOWN,
    ARROW_LEFT,
} InputKey_t;

class Input
{

    /**
     * The Input's constructor should always be private to prevent direct
     * construction calls with the `new` operator.
     */

protected:
    Input(void);

    static Input* input_;

public:

    /**
     * Inputs should not be cloneable.
     */
    Input(Input &other) = delete;

    ~Input(void);

    /**
     * Inputs should not be assignable.
     */
    void operator=(const Input &) = delete;

    /**
     * This is the static method that controls the access to the Input
     * instance. On the first run, it creates a Input object and places it
     * into the static field. On subsequent runs, it returns the client existing
     * object stored in the static field.
     */
    static Input *GetInstance(void);

    /**
     * @brief Begin Input mode
     * 
     */
    void begin(void);

    /**
     * @brief End Input mode
     * 
     * If not called, terminal will no longer print pressed keys.
     */
    void end(void);

    /**
     * @brief Return any key
     * 
     * @return char 
     */
    char waitForKey(void);

    /**
     * @brief Return Control key defined in InputKey_t
     * 
     * Control keys could be (arrow, enter, space, suppr, ...)
     * 
     * @return InputKey_t Key pressed
     */
    InputKey_t waitCtrlKey(void);
};


#endif  /* INPUT_H_ */
