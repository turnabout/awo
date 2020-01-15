#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Game/Inputs/button_state.h"

/*! @brief Every key used by the game.
 *
 * @note When updating this, also update GAME_KEYS in mouse.c with the corresponding GLFW buttons.
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

/*! @brief Initializes the module keeping keys' current state updated.
 *
 *  @param[in] window The game's window.
 */
void init_keyboard_module(GLFWwindow* window);

/*! @brief Updates the button state of every key used by the game.
 */
void update_keyboard_state();

/*! @brief Gets the state of the given key.
 *
 *  @param[in] key The key to check.
 *  @return The current state of the given key represented by a Button_State.
 */
Button_State get_key_state(Key key);

/*! @brief Frees the memory occupied by the keys state module.
 */
void free_keyboard_module();
