#pragma warning( disable : 6308 28182 )

#include <stdlib.h>

#include "conf.h"
#include "Game/Entity/Tile/_tile.h"

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

    // Get the tile's animation.
    gather_tile_data(tiles_data, type, variation, NULL, NULL, &tile->animation);

    // Set the appropriate render grid update callback function
    // Use multi-layered cb if height of frame is that of two regular-sized frames
    if (tile->animation->frames->height == (DEFAULT_TILE_SIZE * 2)) {
        tile->update_render_grid = _old_update_multi_layered_tile_render_grid;
    } else {
        tile->update_render_grid = _old_update_regular_tile_render_grid;
    }

    return tile;
}

void register_tile_board_position(Tile* tile, Uint8 x, Uint8 y)
{
    tile->positions = realloc(tile->positions, sizeof(Point) * (tile->count + 1));

    tile->positions[tile->count].x = x;
    tile->positions[tile->count++].y = y;

    // Update the render grid
    tile->update_render_grid(tile, 0);
}

void free_tile(Tile* tile)
{
    if (tile != NULL) {
        free(tile->positions);
        free(tile);
    }
}