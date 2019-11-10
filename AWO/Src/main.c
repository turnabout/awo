#include <stdio.h>
#include "conf.h"
#include "Game/game.h"

#ifndef __EMSCRIPTEN__
int main(int argc, char** argv)
{
    Game* game;

    if ((game = init_game(
        DEFAULT_GAME_BOARD_WIDTH, 
        DEFAULT_GAME_BOARD_HEIGHT,
        DEFAULT_WINDOW_WIDTH,
        DEFAULT_WINDOW_HEIGHT
    )) == NULL) {
        exit_game(game);
        return 1;
    }

    run_game(game);
    exit_game(game);

    return 0;
}
#endif
