#include "Game/Entity/Unit/_unit.h"

void update_unit_render_grid(Game_Renderer* renderer, void* unit, Uint8 animation_index)
{
    Frame* frame = &((Unit*)unit)->idle_animation->frames[animation_index];

    update_tile_layer_pixel_low(
        renderer,
        UNIT_LAYER,
        ((Unit*)unit)->x,
        ((Unit*)unit)->y,
        (vec2) { frame[0].raw_top_left[0], frame[0].raw_top_left[1] + DEFAULT_TILE_SIZE }
    );
}