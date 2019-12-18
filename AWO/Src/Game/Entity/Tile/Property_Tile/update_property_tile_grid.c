#include "conf.h"
#include "Game/ENtity/Tile/Property_Tile/_property_tile.h"

void update_property_render_grid(Game_Renderer* renderer, void* tile, Uint8 animation_index)
{
    Frame* frame = *((Property_Tile*)tile)->frame;

    // Draw bottom part of property on lower layer
    update_tile_layer_pixel_low(
        renderer,
        TILE_LAYER_0,
        ((Property_Tile*)tile)->x,
        ((Property_Tile*)tile)->y,
        (vec2) { frame[0].raw_top_left[0], frame[0].raw_top_left[1] + DEFAULT_TILE_SIZE }
    );

    // Draw top part of property on higher layer
    update_tile_layer_pixel_low(
        renderer,
        TILE_LAYER_1,
        ((Property_Tile*)tile)->x,
        ((Property_Tile*)tile)->y,
        (vec2) { frame[0].raw_top_left[0], frame[0].raw_top_left[1] }
    );
}

void update_base_render_grid(Game_Renderer* renderer, void* tile, Uint8 animation_index)
{
    Frame* frame = *((Property_Tile*)tile)->frame;

    // Draw base on lower layer
    update_tile_layer_pixel_low(
        renderer,
        TILE_LAYER_0,
        ((Property_Tile*)tile)->x,
        ((Property_Tile*)tile)->y,
        (vec2) { frame[0].raw_top_left[0], frame[0].raw_top_left[1] + DEFAULT_TILE_SIZE }
    );

    // Draw base smoke on higher layer
    update_tile_layer_pixel_low(
        renderer,
        TILE_LAYER_1,
        ((Property_Tile*)tile)->x,
        ((Property_Tile*)tile)->y,
        (vec2) {
            ((Property_Tile*)tile)->base_smoke->frames[animation_index].raw_top_left[0],
            ((Property_Tile*)tile)->base_smoke->frames[animation_index].raw_top_left[1] 
        }
    );
}
