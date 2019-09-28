#include "Visuals/visuals_data.h"
#include "game.h"

void exit_game(Game* game)
{
    if (game->ss != NULL) {
        SDL_DestroyTexture(game->ss);
    }

    if (game->rend != NULL) {
        SDL_DestroyRenderer(game->rend);
    }

    if (game->win != NULL) {
        SDL_DestroyWindow(game->win);
    }

    free(game);
    SDL_Quit();
}
