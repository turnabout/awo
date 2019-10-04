#ifdef __EMSCRIPTEN__

#include <emscripten.h>
#include <SDL.h>
#include "conf.h"
#include "Game/game.h"

// Initialize AWO game.
Game* init_AWO(int w, int h)
{
    Game* game;
    Game_Arg_Weathers weathers = Game_Arg_Clear | Game_Arg_Snow | Game_Arg_Rain;

    if ((game = init_game(weathers, w, h)) == NULL) {
        exit_game(game);
        return NULL;
    }

    return game;
}

// Run AWO game.
void run_AWO(Game* game)
{
	emscripten_set_main_loop_arg(run_game, game, FPS, 1);
}

// Updates the game's viewport size.
void update_game_size(Game* game, int w, int h)
{
    SDL_SetWindowSize(game->win, w, h);
    SDL_RenderSetScale(game->rend, 1.0, 1.0);

    SDL_Rect new_viewport = {0, 0, w, h};
    SDL_RenderSetViewport(game->rend, &new_viewport);
}
#endif
