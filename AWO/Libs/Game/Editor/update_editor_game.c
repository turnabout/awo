#pragma once

#include "Game/Editor/_editor_game.h"

void update_editor_game(Editor_Game* game, float delta_time)
{
    update_keyboard_state(game->keyboard_state);
    update_mouse_state(game->mouse_state);
}