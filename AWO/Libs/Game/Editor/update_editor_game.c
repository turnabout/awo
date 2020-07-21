#include "Game/Editor/_editor_game.h"

void update_editor_game(void* game_arg, float delta_time)
{
    Editor_Game* game = (Editor_Game*)game_arg;
    update_clock(game->clock, delta_time);
    update_keyboard_state(game->keyboard_state);
    update_mouse_state(game->mouse_state);
}