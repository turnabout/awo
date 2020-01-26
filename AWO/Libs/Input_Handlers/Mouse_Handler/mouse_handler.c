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

    handler->scroll_events[handler->scroll_events_count].vertical_scroll = (float)y;
    handler->scroll_events[handler->scroll_events_count].horizontal_scroll = (float)x;
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

    GLFWwindow* glfw_window = get_game_window_GLFW_window_handle(game_window);

    mouse_handler->glfw_window = glfw_window;
    mouse_handler->scroll_events_count = 0;
    handler = mouse_handler;

    // Set mouse callbacks
    glfwSetCursorPosCallback(glfw_window, mouse_cursor_cb);
    glfwSetScrollCallback(glfw_window, mouse_scroll_cb);

    return mouse_handler;

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

void free_mouse_handler(Mouse_Handler* handler)
{
    if (handler == NULL) {
        return;
    }

    free(handler);
    handler = NULL;
}
