#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Game/Inputs/button_state.h"

/*! @brief Every mouse button used by the game.
 *
 * @note When updating this, also update GAME_MOUSE_BUTTONS in mouse_state.c with the corresponding
 * GLFW buttons.
 */
typedef enum Mouse_Button {
    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT,
} Mouse_Button;

/*! @brief The full current state of the mouse.
 */
typedef struct Mouse_State {

    // State of the mouse buttons.
    Button_State* buttons;

    // Scroll wheel value. Negative values are an upward scroll, positive are downward.
    float scroll;

    // Coordinates of the mouse pointer.
    int x, y;

} Mouse_State;

/*! @brief Initializes the module keeping the mouse's current state updated.
 *
 *  @param[in] window The game's window.
 *  @param[in] game_window_height_ptr Pointer to the game's window tiles_height, updated when the 
 *  game is resized.
 */
void init_mouse_module(GLFWwindow* window, int* game_window_height_ptr);

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

/*! @brief Gets the current mouse scroll wheel value.
 *
 *  @return The scroll wheel value.
 */
float get_mouse_scroll_value();

/*! @brief Frees the memory occupied by the mouse state module.
 */;
void free_mouse_module();