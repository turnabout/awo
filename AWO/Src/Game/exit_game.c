#include <stdio.h>
#include <stdlib.h>

#include "Game/Inputs/inputs.h"
#include "Game/_game.h"

void exit_game(Game* game)
{
    glfwTerminate();

    free_tiles_data(game->tiles_data);
    free_units_data(game->units_data);
    free_game_clock(game->clock);
    free_keys_state_module();

    if (game != NULL) {
        free(game);
    }
}
