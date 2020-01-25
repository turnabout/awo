#include <stdlib.h>

#include "Input_Handlers/Keyboard_Handler/_keyboard_handler.h"

// Static reference to the keyboard handler, so we can make use of the key change callback.
static Keyboard_Handler* keyboard_handler = NULL;

void key_change_cb(GLFWwindow* glfw_window, int key, int scancode, int action, int mods)
{
    if (keyboard_handler == NULL || action == GLFW_REPEAT) {
        return;
    }

    keyboard_handler->key_events[keyboard_handler->key_events_count].key = key;
    keyboard_handler->key_events[keyboard_handler->key_events_count].action = action;
    keyboard_handler->key_events_count++;
}

Keyboard_Handler* create_keyboard_handler(Game_Window* game_window)
{
    if (keyboard_handler != NULL) {
        return NULL;
    }

    Keyboard_Handler* handler = malloc(sizeof(Keyboard_Handler));

    if (handler == NULL) {
        return NULL;
    }

    handler->key_events_count = 0;
    handler->game_window = game_window;

    glfwSetKeyCallback(get_game_window_GLFW_window_handle(handler->game_window), key_change_cb);


    keyboard_handler = handler;
    return handler;
}

void process_keyboard_handler_events(Keyboard_Handler* handler, Keyboard_State* state)
{
    // Loop every queued events & process, attaching new states to Keyboard_State
    while (handler->key_events_count) {

        // Keyboard_Event event = handler->queued_events[handler->queued_events_count - 1];
        // TODO
        handler->key_events_count--;
    }
}

void free_keyboard_handler(Keyboard_Handler* handler)
{
    if (handler == NULL) {
        return;
    }

    glfwSetKeyCallback(get_game_window_GLFW_window_handle(handler->game_window), NULL);
    free(handler);

    keyboard_handler = NULL;
}