#include <stdio.h>
#include <stdlib.h>

#include "conf.h"
#include "game.h"

int main(int argc, char** argv)
{
    AWO* game;

    if ((game = create_game(
        DEFAULT_WINDOW_WIDTH,
        DEFAULT_WINDOW_HEIGHT
    )) == NULL) {
        printf("Failed to initialize game\n");
        free_game(game);
        return 1;
    }

    run_game(game);
    free_game(game);

    return 0;
}