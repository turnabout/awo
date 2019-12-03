#include <stdlib.h>

#include "Game/_game.h"

void exit_game(Game* game)
{
    glfwTerminate();

    if (game != NULL) {
        free_game_board(game->board);
        free_tiles_data(game->tiles_data);
        free_units_data(game->units_data);
        free_game_clock(game->clock);
        free_keyboard_module();
        free_mouse_module();
        free(game);
    }
}
