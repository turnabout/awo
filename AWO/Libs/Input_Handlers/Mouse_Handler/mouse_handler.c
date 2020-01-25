#include <stdlib.h>

#include "Input_Handlers/Mouse_Handler/_mouse_handler.h"

// Static reference to the mouse handler, so we can make use of the change callbacks.
static Mouse_Handler* handler = NULL;

void mouse_scroll_cb(GLFWwindow* window, double x, double y)
{
    if (handler->scroll_events_count >= MAX_MOUSE_EVENTS) {
        return;
    }

    handler->scroll_events[handler->scroll_events_count].vertical_scroll = (float)y;
    handler->scroll_events[handler->scroll_events_count].horizontal_scroll = (float)y;
    handler->scroll_events_count++;
}

Mouse_Handler* create_mouse_handler(Game_Window* game_window)
{
    if (handler != NULL) {
        return NULL;
    }

    Mouse_Handler* mouse_handler = malloc(sizeof(Mouse_Handler));

    if (mouse_handler == NULL) {
        return NULL;
    }

    mouse_handler->move_events_count = 0;
    mouse_handler->scroll_events_count = 0;
    handler = mouse_handler;

    return mouse_handler;

}

void free_mouse_handler(Mouse_Handler* handler)
{
    if (handler == NULL) {
        return;
    }

    free(handler);
}

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

/*
#include <stdlib.h>

#include "types.h"
#include "Game/Inputs/Mouse/mouse.h"

// Every GLFW button definition corresponding to the game mouse buttons
static const int GAME_MOUSE_BUTTONS[] = { 
    GLFW_MOUSE_BUTTON_LEFT,
    GLFW_MOUSE_BUTTON_RIGHT,
};

static const int GAME_MOUSE_BUTTONS_COUNT = sizeof(GAME_MOUSE_BUTTONS) / sizeof(int);

// Whether the mouse module has been initialized
Bool initialized = FALSE;

// Reference to the game's window
static GLFWwindow* window_instance;

// The current state of the mouse
static Mouse_State* mouse_state;

// Temporary mouse scroll value
static float fetched_mouse_scroll_value;

void mouse_cursor_cb(GLFWwindow* window, double x, double y)
{
    mouse_state->x = (int)x;
    mouse_state->y = (int)y;
}

void mouse_scroll_cb(GLFWwindow* window, double x, double y)
{
    fetched_mouse_scroll_value = (float)y;
}

Mouse_State* init_mouse_module(GLFWwindow* window)
{
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
}

void update_mouse_module_state()
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

void free_mouse_module(Mouse_State* state)
{
    if (state != NULL) {
        free(state);
    }

    initialized = FALSE;
}
*/
