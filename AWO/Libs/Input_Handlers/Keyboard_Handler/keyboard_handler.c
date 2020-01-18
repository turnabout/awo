#include <stdlib.h>

#include "Input_Handlers/Keyboard_Handler/_keyboard_handler.h"

Keyboard_Handler* create_keyboard_handler(Game_Window* game_window)
{
    Keyboard_Handler* handler = malloc(sizeof(Keyboard_Handler));

    if (handler == NULL) {
        return NULL;
    }

    return handler;
}

void free_keyboard_handler(Keyboard_Handler* handler)
{
    if (handler == NULL) {
        return;
    }

    free(handler);
}