#include <stdlib.h>

#include "Game/_game.h"

void free_game(Game* game)
{
    glfwTerminate();

    if (game == NULL) {
        return;
    }

    free_game_data(game->data);
    free_keyboard_module();
    free_mouse_module(game->mouse_state);
    free_game_cursor(game->pointer);

    free(game);
}
