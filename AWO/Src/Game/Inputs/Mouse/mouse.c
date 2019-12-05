#include <stdlib.h>

#include "Game/Inputs/Mouse/mouse.h"

// Every GLFW button definition corresponding to the game mouse buttons
static const int GAME_MOUSE_BUTTONS[] = { 
    GLFW_MOUSE_BUTTON_LEFT,
    GLFW_MOUSE_BUTTON_RIGHT,
};

static const int GAME_MOUSE_BUTTONS_COUNT = sizeof(GAME_MOUSE_BUTTONS) / sizeof(int);

// Reference to the game's window
static GLFWwindow* window_instance;

// The current state of the mouse
static Mouse_State* mouse_state;

// Temporary mouse scroll value
static float fetched_mouse_scroll_value;

// Pointer to the game's tiles_height. Necessary to update the mouse's Y value.
static int* game_window_height;

void update_mouse_buttons_state()
{
    for (int i = 0; i < GAME_MOUSE_BUTTONS_COUNT; i++) {
        Button_State previous_state = mouse_state->buttons[i];
        int current_down_state = glfwGetMouseButton(window_instance, GAME_MOUSE_BUTTONS[i]);

        mouse_state->buttons[i] = glfwGetMouseButton(window_instance, GAME_MOUSE_BUTTONS[i]) | 
                        ((previous_state & 1) ^ current_down_state) << 1;
    }

    // Update the current mouse scroll value
    mouse_state->scroll = fetched_mouse_scroll_value;
    fetched_mouse_scroll_value = 0;
}

void mouse_cb(GLFWwindow* window, double x, double y)
{
    mouse_state->x = (int)x;
    mouse_state->y = (int)y;
}

void mouse_scroll_cb(GLFWwindow* window, double x, double y)
{
    fetched_mouse_scroll_value = (float)y;
}

void init_mouse_module(GLFWwindow* window, int* window_height)
{
    window_instance = window;
    game_window_height = window_height;

    glfwSetCursorPosCallback(window, mouse_cb);
    glfwSetScrollCallback(window, mouse_scroll_cb);

    mouse_state = malloc(sizeof(Mouse_State));
    
    mouse_state->buttons = malloc(sizeof(Button_State) * GAME_MOUSE_BUTTONS_COUNT);
    mouse_state->scroll = 0;

    for (int i = 0; i < GAME_MOUSE_BUTTONS_COUNT; i++) {
        mouse_state->buttons[i] = BUTTON_UP;
    }
}

Button_State get_mouse_button_state(Mouse_Button mouse_button)
{
    return mouse_state->buttons[mouse_button];
}

float get_mouse_scroll_value()
{
    return mouse_state->scroll;
}

void get_mouse_position(int* x, int* y)
{
    *x = mouse_state->x;
    *y = mouse_state->y;
}

void free_mouse_module()
{
    if (mouse_state != NULL) {
        free(mouse_state);
    }
}
