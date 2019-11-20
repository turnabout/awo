#include "Game/Entity/Tile/tile.h"
#include "Game/Renderer/game_renderer.h"
#include "Game/Data/Palette/game_palette.h"

/*
void update_regular_tile_fog_status(Tile* tile, Bool fog)
{
    update_tile_layer_pixel_high(
        TILE_LAYER_0,
        tile->x,
        tile->y,
        (vec2) {
            get_active_tile_palette_index(fog),
            0.0f
        }
    );
}
*/

/*
void update_multi_layered_tile_fog_status(Tile* tile, Bool fog)
{
    update_tile_layer_pixel_high(
        TILE_LAYER_0,
        tile->x,
        tile->y,
        (vec2) {
            get_active_tile_palette_index(fog),
            0.0f
        }
    );

    update_tile_layer_pixel_high(
        TILE_LAYER_1,
        tile->x,
        tile->y,
        (vec2) {
            get_active_tile_palette_index(fog),
            0.0f
        }
    );
}
*/
