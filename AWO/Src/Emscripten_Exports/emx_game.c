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
void EMX update_game_size(Game* game, int w, int h)
{
    printf("New dimensions: {%d, %d}\n", w, h);

    /*
    SDL_SetWindowSize(game->win, w, h);
    SDL_RenderSetScale(game->rend, 1.0, 1.0);

    SDL_Rect new_viewport = {0, 0, w, h};
    SDL_RenderSetViewport(game->rend, &new_viewport);

    game->w = w;
    game->h = h;
    */
}
