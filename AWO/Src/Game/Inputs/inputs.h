#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Every key used by the game
typedef enum Key {
    KEY_SPACE,
    KEY_1,
    KEY_A,
} Key;

// Every GLFW key definition corresponding to the game keys
static const int GAME_KEYS[] = { 
    GLFW_KEY_SPACE,
    GLFW_KEY_1,
    GLFW_KEY_A
};

static const int GAME_KEYS_COUNT = sizeof(GAME_KEYS) / sizeof(int);

// Every possible key state.
// Key states are represented by a simple 2-bit digit.
// The first bit determines whether the key is pressed down.
// The second bit determines whether the key was just changed this frame.
typedef enum Button_State {
    KEY_UP         = 0,
    KEY_DOWN       = 1,
    KEY_UP_START   = 2,
    KEY_DOWN_START = 3,
} Button_State;

/*! @brief Initializes the module keeping keys current state updated.
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
 *
 *  @param[in] game The main game struct object.
 *  @param[in] sprite_sheet_w The width of the game's loaded sprite sheet.
 *  @param[in] sprite_sheet_h The height of the game's loaded sprite sheet.
 *  @return 1 if successful, 0 if an error occurred.
 */
void free_keys_state_module();