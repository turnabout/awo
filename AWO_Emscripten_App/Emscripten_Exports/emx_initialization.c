#include <stdio.h>

#include "conf.h"
#include "Game/_game.h"
#include "Emscripten_Exports/emx.h"

// Initializes the game.
Game* EMX init_AWO(int w, int h)
{
    Game* game;

    if ((game = create_game(
        DEFAULT_WINDOW_WIDTH,
        DEFAULT_WINDOW_HEIGHT
    )) == NULL) {
        printf("Failed to initialize game\n");
        exit_game(game);
        return NULL;
    }

    return game;
}

// Runs the game.
void EMX run_AWO(Game* game)
{
    emscripten_set_main_loop_arg(game_loop, game, FPS, 1);
}
