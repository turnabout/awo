#include "Visuals/visuals_data.h"
#include "game.h"

void exit_game(Game* game)
{
    if (game->win != NULL) {
        SDL_DestroyWindow(game->win);
    }

    if (game->rend != NULL) {
        SDL_DestroyRenderer(game->rend);
    }

    if (game->ss != NULL) {
        SDL_DestroyTexture(game->ss);
    }

    SDL_Quit();
}
