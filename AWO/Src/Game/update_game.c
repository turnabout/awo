#include "Game/_game.h"

void update_game(Game* game, float delta_time)
{
    update_keys_state();
    update_mouse_buttons_state();
    update_game_clock(game->clock, delta_time);

    update_game_board(game->board);
}