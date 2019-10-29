#include <stdio.h>
#include <stdlib.h>

#include "Game/_game.h"

void exit_game(Game* game)
{
    glfwTerminate();

    free_tiles_data(game->tiles_data);
    free_units_data(game->units_data);
    free_game_clock(game->clock);

    if (game != NULL) {
        free(game);
    }
}
