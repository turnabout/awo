#ifdef __EMSCRIPTEN__
#include "Emscripten_Exports/emx.h"
#endif

#include <stdio.h>
#include "conf.h"
#include "Game/game.h"

#ifndef __EMSCRIPTEN__
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
#else
int main(int argc, char** argv)
{
    printf("Hello world\n");
}
#endif
