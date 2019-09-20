#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "conf.h"
#include "Game/game.h"

int main(int argc, char** argv)
{
    Game game;
    if (init_game(&game) == ERR) {
        exit_game(&game);
        return 1;
    }

    run_game(&game);
    exit_game(&game);

    return 0;
}
