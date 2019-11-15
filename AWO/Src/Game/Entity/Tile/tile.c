#pragma warning( disable : 6308 28182 )

#include <stdlib.h>

#include "conf.h"
#include "Game/Entity/Tile/tile.h"

Tile* create_tile(
    Game_Clock* game_clock, 
    Tiles_Data* tiles_data, 
    Tile_Type type, 
    Tile_Variation variation
)
{
    Tile* tile = (Tile*)malloc(sizeof(Tile));

    tile->type = type;
    tile->variation = variation;
    tile->count = 0;
    tile->positions = NULL;
    tile->animation_index = 0;

    // Get the tile's animation.
    gather_tile_data(tiles_data, type, variation, NULL, NULL, &tile->animation);

    return tile;
}

void update_tile_render_grid(Tile* tile)
{
    update_tile_layer_pixels_low(
        TILE_LAYER_0,
        tile->positions,
        tile->count,
        (vec2) {
            tile->animation->frames[tile->animation_index].raw_top_left[0],
            tile->animation->frames[tile->animation_index].raw_top_left[1]
        }
    );
}

void register_tile_board_position(Tile* tile, Uint8 x, Uint8 y)
{
    tile->positions = realloc(tile->positions, sizeof(Point) * (tile->count + 1));

    tile->positions[tile->count].x = x;
    tile->positions[tile->count++].y = y;
}

void update_tile_animation_index(Tile* tile, Uint8 index)
{
    tile->animation_index = index;
    update_tile_render_grid(tile);
}

void free_tile(Tile* tile)
{
    if (tile != NULL) {
        free(tile);
        // TODO: free game board positions
    }
}