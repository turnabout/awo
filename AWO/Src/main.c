#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "conf.h"
#include "Game/game.h"

int main(int argc, char** argv)
{
    Game game;
    Game_Arg_Weathers weathers = Game_Arg_Clear | Game_Arg_Snow | Game_Arg_Rain;

    if (init_game(&game, weathers) == ERR) {
        exit_game(&game);
        return 1;
    }

    run_game(&game);
    exit_game(&game);

    return 0;
}
