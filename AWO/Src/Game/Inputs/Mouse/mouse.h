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
 *  @return Pointer to the mouse state.
 */
Mouse_State* init_mouse_module(GLFWwindow* window);

/*! @brief Updates the state of every mouse button.
 */
void update_mouse_module_state();

/*! @brief Frees the memory occupied by the mouse state module.
 */;
void free_mouse_module();