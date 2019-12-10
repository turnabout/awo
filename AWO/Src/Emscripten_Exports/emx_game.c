#include "conf.h"
#include "Emscripten_Exports/emx.h"
#include "Game/_game.h"

// Initializes the game.
Game* EMX init_AWO(int w, int h)
{
    Game* game;

    if ((game = init_game(
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

// Updates the game's viewport dimensions.
void EMX update_game_size(Game* game, int width, int height)
{
    printf("New dimensions: {%d, %d}\n", width, height);
    update_game_window_dimensions(game, width, height);
}
