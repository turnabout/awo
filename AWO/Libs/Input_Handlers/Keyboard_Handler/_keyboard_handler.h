#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Input_Handlers/Keyboard_Handler/keyboard_handler.h"
#include "Input_State/Keyboard_State/keyboard_state.h"
#include "Linked_List/linked_list.h"

#define MAX_KEYBOARD_EVENTS 10

typedef struct Keyboard_Event {

    // The key this event acts upon.
    Key key;

    // GLFW_PRESS or GLFW_RELEASE
    int action;

} Keyboard_Event;

struct Keyboard_Handler {

    // Reference to the game window.
    Game_Window* game_window;

    // Keyboard key events queued up & ready to be processed.
    Keyboard_Event queued_events[MAX_KEYBOARD_EVENTS];

    // Amount of events currently queued.
    int queued_events_count;

};