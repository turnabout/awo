#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "types.h"
#include "Input_Handlers/Keyboard_Handler/keyboard_handler.h"
#include "Input_State/Keyboard_State/keyboard_state.h"
#include "Linked_List/linked_list.h"
#include "Linked_List/list_entry.h"

#define MAX_KEYBOARD_EVENTS 10

typedef struct Key_Event {

    // The key this event acts upon.
    Key key;

    // Whether the key's new state is pressed or released.
    Bool pressed;

    // Whether the key event was newly produced in this frame.
    Bool new;

} Key_Event;

/*! @brief List of key events following the same implementation as a generic Linked_List.
 */
typedef struct Key_Events_List {
    List_Entry* head;
    List_Entry* tail;
} Key_Events_List;

struct Keyboard_Handler {

    // Reference to the game window.
    Game_Window* game_window;

    // List of key events queued up.
    Key_Events_List* key_events;

};