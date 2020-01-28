#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Input_State/Headers/button_state.h"

/*! @brief Every mouse button used by the game.
 *
 * @note When updating this, also update GAME_MOUSE_BUTTONS with the corresponding GLFW mouse
 * buttons.
 */
typedef enum Mouse_Button {
    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT,
} Mouse_Button;

// Every GLFW button definition corresponding to the game mouse buttons
static const int GAME_MOUSE_BUTTONS[] = { 
    GLFW_MOUSE_BUTTON_LEFT,
    GLFW_MOUSE_BUTTON_RIGHT,
};

static const int GAME_MOUSE_BUTTONS_COUNT = sizeof(GAME_MOUSE_BUTTONS) / sizeof(int);

/*! @brief Struct holding the current state of the user's mouse.
 */
typedef struct Mouse_State {

    // State of the mouse buttons.
    Button_State* buttons;

    // Scroll wheel value. Negative values are an up/left scroll, positive are a down/right scroll.
    float scroll_y, scroll_x;

    // Coordinates of the mouse pointer.
    int x, y;

} Mouse_State;

Mouse_State* create_mouse_state();
void free_mouse_state(Mouse_State* state);
