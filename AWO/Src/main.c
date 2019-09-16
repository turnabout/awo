#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <stdio.h>
#include <SDL.h>

#include "conf.h"
#include "game.h"
#include "init.h"

#include "Visuals/processing.h"

int main(int argc, char** argv)
{
    Game game;
    if (init_game(&game) == ERR) {
        exit_game(&game);
        return 1;
    }

    // Draw test using unit texture
    SDL_Texture* units_OS = create_units_texture(&game, OS, OS);

    SDL_RenderClear(game.rend);

    SDL_Rect dst;

    dst.x = 0;
    dst.y = 0;
    dst.w = 293;
    dst.h = 275;

    SDL_RenderCopy(game.rend, units_OS, NULL, &dst);
    SDL_RenderPresent(game.rend);

    SDL_Delay(3000);

    // Exit
    exit_game(&game);
    return 0;
}
