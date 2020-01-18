#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Inputs_State/Headers/button_state.h"

/*! @brief Every key used by the game.
 *
 * @note When updating this, also update GAME_KEYS in _keyboard_state.h with the corresponding 
 * GLFW keys.
 */
typedef enum Key {
    KEY_SPACE,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_W,
    KEY_A,
    KEY_S,
    KEY_D,
    KEY_F,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_LEFT_ALT,
} Key;

// Every GLFW key definition corresponding to the game keys
static const int GAME_KEYS[] = { 
    GLFW_KEY_SPACE,
    GLFW_KEY_1,
    GLFW_KEY_2,
    GLFW_KEY_3,
    GLFW_KEY_4,
    GLFW_KEY_5,
    GLFW_KEY_W,
    GLFW_KEY_A,
    GLFW_KEY_S,
    GLFW_KEY_D,
    GLFW_KEY_F,
    GLFW_KEY_UP,
    GLFW_KEY_DOWN,
    GLFW_KEY_LEFT,
    GLFW_KEY_RIGHT,
    GLFW_KEY_LEFT_ALT,
};

static const int GAME_KEY_COUNT = sizeof(GAME_KEYS) / sizeof(int);

/*! @brief Struct holding the current state of the user's keyboard.
 */
typedef struct Keyboard_State {

    // State of the keyboard's keys.
    Button_State* keys;

} Keyboard_State;

Keyboard_State* create_keyboard_state();

void free_keyboard_state(Keyboard_State* state);