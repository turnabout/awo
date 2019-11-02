#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Every possible state for a button
// Button states are represented by a simple 2-bit digit.
// The first bit determines whether the key is pressed down.
// The second bit determines whether the key was just changed this frame.
typedef enum Button_State {
    BUTTON_UP         = 0,
    BUTTON_DOWN       = 1,
    BUTTON_UP_START   = 2,
    BUTTON_DOWN_START = 3,
} Button_State;

// Every key used by the game
// NOTE: When updating this, also update GAME_KEYS in keys_state.c with the corresponding glfw 
// keys.
typedef enum Key {
    KEY_SPACE,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_A,
    KEY_S,
    KEY_D,
    KEY_F,
} Key;

// Every mouse button used by the game
// NOTE: When updating this, also update GAME_MOUSE_BUTTONS in mouse_state.c with the corresponding
// glfw buttons.
typedef enum Mouse_Button {
    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT,
} Mouse_Button;

/*! @brief Initializes the module keeping keys' current state updated.
 *
 *  @param[in] window The game's window.
 */
void init_keys_state_module(GLFWwindow* window);

/*! @brief Updates the button state of every key used by the game.
 */
void update_keys_state();

/*! @brief Gets the state of the given key.
 *
 *  @param[in] key The key to check.
 *  @return The current state of the given key represented by a Button_State.
 */
Button_State get_key_state(Key key);

/*! @brief Frees the memory occupied by the keys state module.
 */
void free_keys_state_module();

/*! @brief Initializes the module keeping the mouse's current state updated.
 *
 *  @param[in] window The game's window.
 *  @param[in] game_window_height_ptr Pointer to the game's window height, updated when the game is
 *  resized.
 */
void init_mouse_state_module(GLFWwindow* window, int* game_window_height_ptr);

/*! @brief Updates the state of every mouse button.
 */
void update_mouse_buttons_state();

/*! @brief Gets the state of the given mouse button.
 *
 *  @param[in] mouse_button The button to check.
 *  @return The current state of the given button represented by a Button_State.
 */
Button_State get_mouse_button_state(Mouse_Button mouse_button);

/*! @brief Gets the current screen position of the mouse cursor.
 *
 *  @param[out] x The x position.
 *  @param[out] y The y position.
 */
void get_mouse_position(int* x, int* y);

/*! @brief Frees the memory occupied by the mouse state module.
 */
void free_mouse_state_module();
