#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "conf.h"
#include "game.h"
#include "init.h"

#include "Visuals/process.h"
#include "Visuals/load.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

void test_json();

int main(int argc, char** argv)
{
    // Initialize
    Game game;
    if (init_game(&game) == ERR) {
        exit_game(&game);
        return 1;
    }

    test_json();

    SDL_Texture* testTex = create_units_texture(&game);

    // Draw test
    SDL_SetRenderDrawBlendMode(game.rend, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(testTex, SDL_BLENDMODE_BLEND);

    SDL_RenderClear(game.rend);

    SDL_Rect dst;

    dst.x = 0;
    dst.y = 0;
    dst.w = 293;
    dst.h = 275;

    SDL_RenderCopy(game.rend, testTex, NULL, &dst);
    SDL_RenderPresent(game.rend);

    SDL_Delay(3000);

    // Exit
    exit_game(&game);
    return 0;
}

void test_json()
{
    load_visuals_data_structure();
}
