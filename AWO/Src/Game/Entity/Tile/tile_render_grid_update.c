#include "conf.h"
#include "Game/Entity/Tile/_tile.h"

void _old_update_regular_tile_render_grid(Tile* tile, Uint8 animation_index)
{
    update_tile_layer_pixels_low(
        TILE_LAYER_0,
        tile->positions,
        tile->count,
        (vec2) {
            tile->animation->frames[animation_index].raw_top_left[0],
            tile->animation->frames[animation_index].raw_top_left[1]
        }
    );
}

void _old_update_multi_layered_tile_render_grid(Tile* tile, Uint8 animation_index)
{
    update_tile_layer_pixels_low(
        TILE_LAYER_0,
        tile->positions,
        tile->count,
        (vec2) {
            tile->animation->frames[animation_index].raw_top_left[0],
            tile->animation->frames[animation_index].raw_top_left[1] + DEFAULT_TILE_SIZE
        }
    );

    update_tile_layer_pixels_low(
        TILE_LAYER_1,
        tile->positions,
        tile->count,
        (vec2) {
            tile->animation->frames[animation_index].raw_top_left[0],
            tile->animation->frames[animation_index].raw_top_left[1]
        }
    );
}
