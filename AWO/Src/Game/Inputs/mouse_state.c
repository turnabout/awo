#include <stdlib.h>

#include "Game/Inputs/inputs.h"

// Every GLFW button definition corresponding to the game mouse buttons
static const int GAME_MOUSE_BUTTONS[] = { 
    GLFW_MOUSE_BUTTON_LEFT,
    GLFW_MOUSE_BUTTON_RIGHT,
};

static const int GAME_MOUSE_BUTTONS_COUNT = sizeof(GAME_MOUSE_BUTTONS) / sizeof(int);

// Reference to the game's window
static GLFWwindow* window_instance;

// Holds the current state of every mouse button
static Button_State* mouse_buttons_state;

// Current mouse coordinates
static int mouse_x = 0;
static int mouse_y = 0;

// Pointer to the game's tiles_height. Necessary to update the mouse's Y value.
static int* game_window_height;

void update_mouse_buttons_state()
{
    for (int i = 0; i < GAME_MOUSE_BUTTONS_COUNT; i++) {
        Button_State previous_state = mouse_buttons_state[i];
        int current_down_state = glfwGetMouseButton(window_instance, GAME_MOUSE_BUTTONS[i]);

        mouse_buttons_state[i] = glfwGetMouseButton(window_instance, GAME_MOUSE_BUTTONS[i]) | 
                        ((previous_state & 1) ^ current_down_state) << 1;
    }
}

void mouse_cb(GLFWwindow* window, double x, double y)
{
    mouse_x = (int)x;

    // Subtract the current game window tiles_height from the mouse position to get the Y coordinate 
    // relative to the lower edge instead of the upper edge.
    mouse_y = abs((int)y - *game_window_height);
}

void init_mouse_state_module(GLFWwindow* window, int* game_window_height_ptr)
{
    window_instance = window;
    game_window_height = game_window_height_ptr;
    glfwSetCursorPosCallback(window, mouse_cb);

    mouse_buttons_state = (Button_State*)malloc(sizeof(Button_State) * GAME_MOUSE_BUTTONS_COUNT);

    for (int i = 0; i < GAME_MOUSE_BUTTONS_COUNT; i++) {
        mouse_buttons_state[i] = 0;
    }
}

Button_State get_mouse_button_state(Mouse_Button mouse_button)
{
    return mouse_buttons_state[mouse_button];
}

void get_mouse_position(int* x, int* y)
{
    *x = mouse_x;
    *y = mouse_y;
}

void free_mouse_state_module()
{
    if (mouse_buttons_state != NULL) {
        free(mouse_buttons_state);
    }
}
