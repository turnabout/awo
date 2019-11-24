#include "conf.h"
#include "Game/Entity/Tile/tile.h"
#include "Game/Renderer/game_renderer.h"

#include "Game/Data/Tile/tiles_data.h"

void update_regular_property_render_grid(Tile* tile, Uint8 animation_index)
{
    // Draw bottom part of property on lower layer
    update_tile_layer_pixel_low(
        TILE_LAYER_0,
        tile->x,
        tile->y,
        (vec2) {
            ((Property_Tile*)tile)->frame[0].raw_top_left[0],
            ((Property_Tile*)tile)->frame[0].raw_top_left[1] + DEFAULT_TILE_SIZE
        }
    );

    // Draw top part of property on higher layer
    update_tile_layer_pixel_low(
        TILE_LAYER_1,
        tile->x,
        tile->y,
        (vec2) {
            ((Property_Tile*)tile)->frame[0].raw_top_left[0],
            ((Property_Tile*)tile)->frame[0].raw_top_left[1]
        }
    );
}

void update_base_render_grid(Tile* tile, Uint8 animation_index)
{
    printf("%d\n", animation_index);

    // Draw base on lower layer
    update_tile_layer_pixel_low(
        TILE_LAYER_0,
        tile->x,
        tile->y,
        (vec2) {
            ((Property_Tile*)tile)->frame[0].raw_top_left[0],
            ((Property_Tile*)tile)->frame[0].raw_top_left[1] + DEFAULT_TILE_SIZE
        }
    );

    // Draw base smoke on higher layer
    update_tile_layer_pixel_low(
        TILE_LAYER_1,
        tile->x,
        tile->y,
        (vec2) {
            ((Property_Tile*)tile)->base_smoke->frames[animation_index].raw_top_left[0],
            ((Property_Tile*)tile)->base_smoke->frames[animation_index].raw_top_left[1] 
        }
    );
}
