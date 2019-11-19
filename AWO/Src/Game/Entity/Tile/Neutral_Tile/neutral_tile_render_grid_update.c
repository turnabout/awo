#include "conf.h"
#include "Game/Entity/Tile/tile.h"
#include "Game/Entity/Tile/Neutral_Tile/neutral_tile.h"

void update_regular_tile_render_grid(Tile* tile, Uint8 animation_index)
{
    // Neutral_Tile* neutral_tile = (Neutral_Tile*)tile->contents;

    /*
    update_tile_layer_pixels_low(
        TILE_LAYER_0,
        neutral_tile->positions,
        tile->count,
        (vec2) {
            neutral_tile->animation->frames[animation_index].raw_top_left[0],
            neutral_tile->animation->frames[animation_index].raw_top_left[1]
        }
    );
    */
}

void update_multi_layered_tile_render_grid(Tile* tile, Uint8 animation_index)
{
    // Neutral_Tile* neutral_tile = (Neutral_Tile*)tile->contents;

    /*
    update_tile_layer_pixels_low(
        TILE_LAYER_0,
        neutral_tile->positions,
        neutral_tile->count,
        (vec2) {
            neutral_tile->animation->frames[animation_index].raw_top_left[0],
            neutral_tile->animation->frames[animation_index].raw_top_left[1] + DEFAULT_TILE_SIZE
        }
    );

    update_tile_layer_pixels_low(
        TILE_LAYER_1,
        neutral_tile->positions,
        neutral_tile->count,
        (vec2) {
            neutral_tile->animation->frames[animation_index].raw_top_left[0],
            neutral_tile->animation->frames[animation_index].raw_top_left[1]
        }
    );
    */
}
