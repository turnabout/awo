#include <stdio.h>
#include <stdlib.h>

#include "Game/_game.h"

void exit_game(Game* game)
{
    // TODO: Free other resources

    if (game != NULL) {
        free(game);
    }
}
