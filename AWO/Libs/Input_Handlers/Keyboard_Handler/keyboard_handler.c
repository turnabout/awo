#include <stdlib.h>

#include "Input_Handlers/Keyboard_Handler/_keyboard_handler.h"

// Static internal reference to the keyboard handler so we can make use of the key change callback.
static Keyboard_Handler* handler = NULL;

void key_change_cb(GLFWwindow* glfw_window, int key, int scancode, int action, int mods)
{
    if (handler == NULL || action == GLFW_REPEAT) {
        return;
    }

    handler->key_events[handler->key_events_count].key = key;
    handler->key_events[handler->key_events_count].pressed =
        (action == GLFW_PRESS)
            ? TRUE
            : FALSE;
    handler->key_events_count++;
}

void create_keyboard_handler(Game_Window* game_window)
{
    if (handler != NULL) {
        return;
    }

    handler = malloc(sizeof(Keyboard_Handler));

    if (handler == NULL) {
        return;
    }

    handler->key_events_count = 0;
    handler->game_window = game_window;

    glfwSetKeyCallback(get_game_window_GLFW_window_handle(handler->game_window), key_change_cb);
}

void update_keyboard_state(Keyboard_State* state)
{
    // Loop every queued events & process, attaching new states to Keyboard_State
    while (handler->key_events_count) {

        Key_Event event = handler->key_events[handler->key_events_count - 1];
        Button_State old = state->keys[event.key];

        state->keys[event.key] = event.pressed | ((old & 1) ^ event.pressed) << 1;
        handler->key_events_count--;
    }
}

void disable_default_keyboard_handler_callbacks()
{
    glfwSetKeyCallback(get_game_window_GLFW_window_handle(handler->game_window), NULL);
}

void free_keyboard_handler()
{
    if (handler == NULL) {
        return;
    }

    glfwSetKeyCallback(get_game_window_GLFW_window_handle(handler->game_window), NULL);

    free(handler);
    handler = NULL;
}