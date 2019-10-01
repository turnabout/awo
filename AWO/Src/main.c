#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <stdio.h>
#include "conf.h"
#include "Game/game.h"

#ifndef __EMSCRIPTEN__
int main(int argc, char** argv)
{
    Game* game;
    Game_Arg_Weathers weathers = Game_Arg_Clear | Game_Arg_Snow | Game_Arg_Rain;

    if ((game = init_game(weathers, SCREEN_WIDTH, SCREEN_HEIGHT)) == NULL) {
        exit_game(game);
        return 1;
    }

    run_game(game);
    exit_game(game);

    return 0;
}
#endif

#ifdef __EMSCRIPTEN__
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
#endif
