#pragma warning( disable : 6308 28182 )

#include <stdlib.h>

#include "conf.h"
#include "Game/Entity/Tile/_tile.h"

Tile* create_tile(
    Game_Clock* game_clock, 
    Tiles_Data* tiles_data, 
    Tile_Type tile_type, 
    Tile_Variation variation
)
{
    Tile* tile = (Tile*)malloc(sizeof(Tile));

    tile->type = tile_type;
    tile->variation = variation;

    tile->count = 0;
    tile->positions = NULL;

    // Get the tile's animation.
    gather_tile_data(tiles_data, tile_type, variation, NULL, NULL, &tile->animation);

    // Set the appropriate render grid update callback function
    // Use multi-layered cb if height of frame is that of two regular-sized frames
    if (tile->animation->frames->height == (DEFAULT_TILE_SIZE * 2)) {
        tile->update_render_grid = _old_update_multi_layered_tile_render_grid;
    } else {
        tile->update_render_grid = _old_update_regular_tile_render_grid;
    }

    if (tile_type >= NEUTRAL_TILE_TYPE_FIRST && tile_type <= NEUTRAL_TILE_TYPE_LAST) {

        // Neutral tile
        tile->contents_type = Tile_Contents_Neutral;

        tile->contents = create_neutral_tile(
            game_clock,
            tiles_data,
            tile_type,
            variation,
            &tile->update_render_grid
        );
    } else if (tile_type >= PROPERTY_TILE_TYPE_FIRST && tile_type <= PROPERTY_TILE_TYPE_LAST) {

        // Property tile
        tile->contents_type = Tile_Contents_Property;

        tile->contents = create_property_tile(
            game_clock,
            tiles_data,
            (Property_Type)(tile_type - PROPERTY_TILE_TYPE_FIRST),
            (Unit_Variation)(variation),
            &tile->update_render_grid
        );
    } else {
        free(tile);
        return NULL;
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