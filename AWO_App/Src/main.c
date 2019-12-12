#include <stdio.h>
#include <stdlib.h>

#include "conf.h"
#include "Game/game.h"
#include "Utilities/Linked_List/linked_list.h"

int main(int argc, char** argv)
{
    Game* game;

    if ((game = init_game(
        DEFAULT_WINDOW_WIDTH,
        DEFAULT_WINDOW_HEIGHT
    )) == NULL) {
        printf("Failed to initialize game\n");
        exit_game(game);
        return 1;
    }

    run_game(game);
    exit_game(game);

    return 0;
}