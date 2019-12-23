#include <stdio.h>
#include <stdlib.h>

#include "AWO/Include/game.h"

int main(int argc, char** argv)
{
    Game* game;

    if ((game = create_game(0, 0)) == NULL) {
        printf("Failed to initialize game\n");
        free_game(game);
        return 1;
    }

    if (prepare_design_room_game(game)) {
        run_game(game);
    }

    free_game(game);

    return 0;
}