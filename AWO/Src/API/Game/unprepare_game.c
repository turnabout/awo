#include "emx.h"
#include "Game/_game.h"

void EMX unprepare_game(Game* game)
{
    free_game_board(game->board);
    free_game_camera(game->camera);
    free_game_clock(game->clock);
    free_game_editor(game->editor);
    free_game_renderer(game->renderer);

    game->board = NULL;
    game->camera = NULL;
    game->clock = NULL;
    game->editor = NULL;
    game->renderer = NULL;
    game->state = Game_Created;
}
