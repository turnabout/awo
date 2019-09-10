#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "conf.h"
#include "Game/init.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

int main(int argc, char** argv)
{
    // Initialize game
    SDL_Window*   window;
    SDL_Renderer* rend;
    SDL_Surface*  ss;

    if (init_game(&window, &rend, &ss) == ERR) {
        return 1;
    }

    printf("Hello world\n");

    SDL_Delay(2000);

    // Exit game
    exit_game(&window, &rend, &ss);

    return 0;
}
