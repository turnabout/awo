#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <stdio.h>
#include <SDL.h>

#include "conf.h"
#include "game.h"
#include "init.h"

#include "Visuals/processing.h"

void draw_test(Game* game);
void run_game(Game* game);

int main(int argc, char** argv)
{
    Game game;
    if (init_game(&game) == ERR) {
        exit_game(&game);
        return 1;
    }

    draw_test(&game);
    run_game(&game);

    return 0;
}

void run_game(Game* game)
{
    while (1) {
        SDL_Event event;
        Uint32 start_ticks = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                exit_game(game);
                return;
            }
        }

        // If frame finished early, wait remaining time
        int frame_ticks = SDL_GetTicks() - start_ticks;

        if (frame_ticks < SCREEN_TICKS_PER_FRAME) {
            SDL_Delay(SCREEN_TICKS_PER_FRAME - frame_ticks);
        }
    }
}

void draw_test(Game* game)
{
    // Draw test using unit texture
    SDL_Texture* units_OS = create_units_texture(game, OS, OS);

    SDL_SetRenderDrawColor(game->rend, 255, 255, 255, 255);
    SDL_RenderClear(game->rend);

    SDL_Rect dst;

    dst.x = 0;
    dst.y = 0;
    dst.w = 293;
    dst.h = 275;

    SDL_RenderCopy(game->rend, units_OS, NULL, &dst);
    SDL_RenderPresent(game->rend);
}
