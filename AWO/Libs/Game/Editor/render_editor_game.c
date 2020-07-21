#include "Game/Editor/_editor_game.h"
#include "Game_Data/UI_Data/UI_data.h"

static Bool init = FALSE;
static Animation* anim = NULL;

void render_editor_game(void* game_arg)
{
    Editor_Game* game = (Editor_Game*)game_arg;
    if (!init) {
        init = TRUE;
        anim = get_UI_element_frames(game->data->UI, TileCursorX);
    }

    // Render the stage
    render_stage(game->stage_renderer);

    // Render extras
    // queue_extra_renderer_extra(game->extras_renderer, (vec2) {100.0f, 100.0f}, &anim->frames[0]);
    // render_queued_extra_renderer_extras(game->extras_renderer);
}