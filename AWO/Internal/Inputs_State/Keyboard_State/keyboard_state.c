#include <stdlib.h>

#include "Inputs_State/Keyboard_State/keyboard_state.h"

Keyboard_State* create_keyboard_state()
{
    Keyboard_State* state = malloc(sizeof(Keyboard_State));

    if (state == NULL) {
        return NULL;
    }

    state->keys = malloc(sizeof(Key) * GAME_KEY_COUNT);

    if (state->keys == NULL) {
        free_keyboard_state(state);
        return NULL;
    }

    for (int i = 0; i < GAME_KEY_COUNT; i++) {
        state->keys[i] = BUTTON_UP;
    }

    return state;
}

void free_keyboard_state(Keyboard_State* state)
{
    if (state == NULL) {
        return;
    }

    if (state->keys != NULL) {
        free(state->keys);
    }

    free(state);
}
