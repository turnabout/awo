#include <stdlib.h>

#include "Input_Handlers/Keyboard_Handler/_keyboard_handler.h"

// Static internal reference to the keyboard handler so we can make use of the key change callback.
static Keyboard_Handler* handler = NULL;

void key_change_cb(GLFWwindow* glfw_window, int key, int scancode, int action, int mods)
{
    if (handler == NULL || action == GLFW_REPEAT) {
        return;
    }

    Key_Event* event = malloc(sizeof(Key_Event));

    event->key = key;
    event->pressed = (action == GLFW_PRESS) ? TRUE : FALSE;
    event->new = TRUE;

    append_linked_list_item((Linked_List*)handler->key_events, (void*)event);
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

    handler->game_window = game_window;
    handler->key_events = (Key_Events_List*)create_linked_list(NULL, 0);

    glfwSetKeyCallback(get_game_window_GLFW_window_handle(handler->game_window), key_change_cb);
}

void update_keyboard_state(Keyboard_State* state)
{
    // Loop every tile entry & update the render grid pixels for every tile in the list
    List_Entry* entry = handler->key_events->head;

    while (entry != NULL) {
        Key_Event* event = (Key_Event*)entry->element;
        Button_State old = state->keys[event->key];

        state->keys[event->key] = event->pressed | ((old & 1) ^ event->pressed) << 1;

        entry = entry->next;

        // Either flag the event as old, or delete it if it already was
        if (event->new == TRUE) {
            event->new = FALSE;
        } else {
            delete_linked_list_item((Linked_List*)handler->key_events, (void*)event, TRUE);
        }
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

    free_linked_list((Linked_List*)handler->key_events);
    free(handler);
    handler = NULL;
}