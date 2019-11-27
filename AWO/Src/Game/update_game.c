#include "Game/_game.h"

void update_game(Game* game, float delta_time)
{
    update_keys_state();
    update_mouse_buttons_state();

    update_game_clock(game->clock, delta_time);
    update_game_board(game->board);

    if (get_key_state(KEY_UP) == BUTTON_DOWN_START) {
        update_game_camera_view_zoom(game->camera, 0.5f);
    }

    if (get_key_state(KEY_DOWN) == BUTTON_DOWN_START) {
        update_game_camera_view_zoom(game->camera, -0.5f);
    }
}