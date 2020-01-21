#include "Input_Handlers/Mouse_Handler/_mouse_handler.h"

// Currently-loaded mouse state.
static Mouse_State* state;

// Reference to the game's window.
static GLFWwindow* window_instance;

// Temporary mouse scroll value.
static float fetched_mouse_scroll_value;

void init_mouse_handler(GLFWwindow* window)
{
    /*
    if (initialized) {
        return NULL;
    }

    window_instance = window;

    // Set mouse callbacks
    glfwSetCursorPosCallback(window, mouse_cursor_cb);
    glfwSetScrollCallback(window, mouse_scroll_cb);

    mouse_state = malloc(sizeof(Mouse_State));
    
    mouse_state->buttons = malloc(sizeof(Button_State) * GAME_MOUSE_BUTTONS_COUNT);
    mouse_state->scroll = 0;

    for (int i = 0; i < GAME_MOUSE_BUTTONS_COUNT; i++) {
        mouse_state->buttons[i] = BUTTON_UP;
    }

    initialized = TRUE;

    return mouse_state;
    */
}
