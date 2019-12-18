#include "conf.h"
#include "Game/Entity/Tile/Neutral/_neutral_tile.h"

void update_tile_render_grid(Game_Renderer* renderer, void* tile, Uint8 animation_index)
{
    update_tile_layer_pixel_low(
        renderer,
        TILE_LAYER_0,
        ((Neutral_Tile*)tile)->x,
        ((Neutral_Tile*)tile)->y,
        (vec2) {
            ((Neutral_Tile*)tile)->animation->frames[animation_index].raw_top_left[0],
            ((Neutral_Tile*)tile)->animation->frames[animation_index].raw_top_left[1]
        }
    );
}

void update_tall_tile_render_grid(Game_Renderer* renderer, void* tile, Uint8 animation_index)
{
    update_tile_layer_pixel_low(
        renderer,
        TILE_LAYER_0,
        ((Neutral_Tile*)tile)->x,
        ((Neutral_Tile*)tile)->y,
        (vec2) {
            ((Neutral_Tile*)tile)->animation->frames[animation_index].raw_top_left[0],
            ((Neutral_Tile*)tile)->animation->frames[animation_index].raw_top_left[1] 
                + DEFAULT_TILE_SIZE
        }
    );

    update_tile_layer_pixel_low(
        renderer,
        TILE_LAYER_1,
        ((Neutral_Tile*)tile)->x,
        ((Neutral_Tile*)tile)->y,
        (vec2) {
            ((Neutral_Tile*)tile)->animation->frames[animation_index].raw_top_left[0],
            ((Neutral_Tile*)tile)->animation->frames[animation_index].raw_top_left[1] 
        }
    );
}
