#include "Game/Data/Palette/game_palette.h"
#include "Game/Entity/Tile/Neutral_Tile/_neutral_tile.h"

void update_tile_palette(Game_Renderer* renderer, void* tile, Bool fog)
{
    update_tile_layer_pixel_high(
        renderer,
        TILE_LAYER_0,
        ((Neutral_Tile*)tile)->x,
        ((Neutral_Tile*)tile)->y,
        (vec2) {
            get_active_tile_palette_index(fog),
            0.0f
        }
    );
}

void update_tall_tile_palette(Game_Renderer* renderer, void* tile, Bool fog)
{
    update_tile_layer_pixel_high(
        renderer,
        TILE_LAYER_0,
        ((Neutral_Tile*)tile)->x,
        ((Neutral_Tile*)tile)->y,
        (vec2) {
            get_active_tile_palette_index(fog),
            0.0f
        }
    );

    update_tile_layer_pixel_high(
        renderer,
        TILE_LAYER_1,
        ((Neutral_Tile*)tile)->x,
        ((Neutral_Tile*)tile)->y,
        (vec2) {
            get_active_tile_palette_index(fog),
            0.0f
        }
    );
}
