#include <stdlib.h>

#include "emx.h"
#include "Game/_game.h"

void EMX free_game(Game* game)
{
    if (game == NULL) {
        glfwTerminate();
        return;
    }

    // Ensure game is "unprepared"
    unprepare_game(game);

    if (game->window != NULL) {
        glfwDestroyWindow(game->window);
    }

    free_game_cursor(game->cursor);
    free_game_data(game->data);
    free_mouse_module(game->mouse_state);

    free_keyboard_module();

    game->cursor = NULL;
    game->data = NULL;
    game->mouse_state = NULL;

    free(game);
}
