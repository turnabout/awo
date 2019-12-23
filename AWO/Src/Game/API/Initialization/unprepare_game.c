#include "Game/_game.h"

void unprepare_game(Game* game)
{
    free_game_renderer(game->renderer);
    free_game_clock(game->clock);
    free_game_camera(game->camera);
    free_game_board(game->board);
}
