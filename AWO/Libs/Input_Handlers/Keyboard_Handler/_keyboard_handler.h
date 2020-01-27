#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Include/types.h"
#include "Input_Handlers/Keyboard_Handler/keyboard_handler.h"
#include "Input_State/Keyboard_State/keyboard_state.h"

#define MAX_KEYBOARD_EVENTS 10

typedef struct Key_Event {

    // The key this event acts upon.
    Key key;

    // Whether the key's new state is pressed or released.
    Bool pressed;

} Key_Event;

struct Keyboard_Handler {

    // Reference to the game window.
    Game_Window* game_window;

    // Keyboard key events queued up & ready to be processed.
    Key_Event key_events[MAX_KEYBOARD_EVENTS];

    // Amount of key events currently queued.
    int key_events_count;

};