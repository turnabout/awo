#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "conf.h"
#include "game.h"
#include "Game/init.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

int main(int argc, char** argv)
{
    // Initialize
    Game game;
    if (init_game(&game) == ERR) {
        exit_game(&game);
        return 1;
    }

    SDL_Delay(2000);
    printf("Hello world\n");

    // Exit
    exit_game(&game);
    return 0;
}
