#include "_editor_game.h"

void update_editor_game(Editor_Game* game, float delta_time)
{
    update_clock(game->clock, delta_time);
    update_keyboard_state(game->keyboard_state);
    update_mouse_state(game->mouse_state);
}