#pragma once

#include "Game/Editor/_editor_game.h"

static Bool init = FALSE;
static Animation* anim = NULL;

void render_editor_game(Editor_Game* game)
{
    if (!init) {
        init = TRUE;
        anim = get_UI_element_frames(game->data->UI, TileCursorX);
    }

    queue_extra_renderer_extra(game->extras_renderer, (vec2) {0.0f, 0.0f}, &anim->frames[0]);
    render_queued_extra_renderer_extras(game->extras_renderer);

}