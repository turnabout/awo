#include <stdlib.h>

#include "Input_Handlers/Mouse_Handler/_mouse_handler.h"

// Static reference to the mouse handler, so we can make use of the change callbacks.
static Mouse_Handler* handler = NULL;

void mouse_cursor_cb(GLFWwindow* window, double x, double y)
{
    handler->x = (int)x;
    handler->y = (int)y;
}

void mouse_scroll_cb(GLFWwindow* window, double x, double y)
{
    if (handler->scroll_events_count >= MAX_MOUSE_EVENTS) {
        return;
    }

    handler->scroll_events[handler->scroll_events_count].y = (float)y;
    handler->scroll_events[handler->scroll_events_count].x = (float)x;
    handler->scroll_events_count++;
}

void create_mouse_handler(Game_Window* game_window)
{
    if (handler != NULL) {
        return;
    }

    handler = malloc(sizeof(Mouse_Handler));

    if (handler == NULL) {
        return;
    }

    GLFWwindow* glfw_window = get_game_window_GLFW_window_handle(game_window);

    handler->glfw_window = glfw_window;
    handler->scroll_events_count = 0;

    // Set mouse callbacks
    glfwSetCursorPosCallback(glfw_window, mouse_cursor_cb);
    glfwSetScrollCallback(glfw_window, mouse_scroll_cb);
}

void update_mouse_state(Mouse_State* state)
{

    // Loop & process all accumulated mouse scroll events
    state->scroll_y = 0.0f;
    state->scroll_x = 0.0f;

    for (int i = 0; i < handler->scroll_events_count; i++) {
        state->scroll_x += handler->scroll_events[i].x;
        state->scroll_y += handler->scroll_events[i].y;
    }

    handler->scroll_events_count = 0;

    // Set new mouse x/y 
    state->x = handler->x;
    state->y = handler->y;
}

void disable_default_mouse_handler_callbacks()
{
    glfwSetCursorPosCallback(handler->glfw_window, NULL);
    glfwSetScrollCallback(handler->glfw_window, NULL);
}

void update_mouse_position(double x, double y)
{
    if (handler != NULL) {
        mouse_cursor_cb(NULL, x, y);
    }
}

void update_mouse_scroll(double x, double y)
{
    if (handler != NULL) {
        mouse_scroll_cb(NULL, x, y);
    }
}

void free_mouse_handler()
{
    if (handler == NULL) {
        return;
    }

    free(handler);
    handler = NULL;
}
