#include <stdlib.h>

#include "Input_State/Keyboard_State/keyboard_state.h"

Keyboard_State* create_keyboard_state()
{
    Keyboard_State* state = malloc(sizeof(Keyboard_State));

    if (state == NULL) {
        return NULL;
    }

    for (Key key = KEY_FIRST; key < KEY_COUNT; key++) {
        state->keys[key] = BUTTON_UP;
    }

    return state;
}

void free_keyboard_state(Keyboard_State* state)
{
    if (state == NULL) {
        return;
    }

    free(state);
}
