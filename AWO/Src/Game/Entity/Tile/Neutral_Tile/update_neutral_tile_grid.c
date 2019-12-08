#include "conf.h"
#include "Game/Entity/Tile/tile.h"
#include "Game/Renderer/game_renderer.h"

void update_regular_tile_render_grid(void* tile, Uint8 animation_index)
{
    update_tile_layer_pixel_low(
        TILE_LAYER_0,
        ((Tile*)tile)->x,
        ((Tile*)tile)->y,
        (vec2) {
            ((Neutral_Tile*)tile)->animation->frames[animation_index].raw_top_left[0],
            ((Neutral_Tile*)tile)->animation->frames[animation_index].raw_top_left[1]
        }
    );
}

void update_multi_layered_tile_render_grid(void* tile, Uint8 animation_index)
{
    update_tile_layer_pixel_low(
        TILE_LAYER_0,
        ((Tile*)tile)->x,
        ((Tile*)tile)->y,
        (vec2) {
            ((Neutral_Tile*)tile)->animation->frames[animation_index].raw_top_left[0],
            ((Neutral_Tile*)tile)->animation->frames[animation_index].raw_top_left[1] 
                + DEFAULT_TILE_SIZE
        }
    );

    update_tile_layer_pixel_low(
        TILE_LAYER_1,
        ((Tile*)tile)->x,
        ((Tile*)tile)->y,
        (vec2) {
            ((Neutral_Tile*)tile)->animation->frames[animation_index].raw_top_left[0],
            ((Neutral_Tile*)tile)->animation->frames[animation_index].raw_top_left[1] 
        }
    );
}
