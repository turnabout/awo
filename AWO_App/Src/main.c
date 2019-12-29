#include <stdio.h>
#include <stdlib.h>

#include "AWO/Include/game.h"

void game_run_callback(Game* game)
{
}

int main(int argc, char** argv)
{
    Game* game;

    if ((game = create_game(0, 0)) == NULL) {
        printf("Failed to initialize game\n");
        free_game(game);
        return 1;
    }

    if (prepare_design_room_game(game)) {
        run_game(game, game_run_callback);
    }

    free_game(game);

    return 0;
}