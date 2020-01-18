#include <stdlib.h>

#include "Inputs_State/Mouse_State/mouse_state.h"

Mouse_State* create_mouse_state()
{
    Mouse_State* state = malloc(sizeof(Mouse_State*));

    if (state == NULL) {
        return NULL;
    }

    state->buttons = malloc(sizeof(Button_State) * GAME_MOUSE_BUTTONS_COUNT);
    state->scroll = 0;
    state->x = 0;
    state->y = 0;

    if (state->buttons == NULL) {
        free_mouse_state(state);
        return NULL;
    }

    return state;
}

void free_mouse_state(Mouse_State* state)
{
    if (state == NULL) {
        return;
    }

    if (state->buttons != NULL) {
        free(state->buttons);
    }

    free(state);

}