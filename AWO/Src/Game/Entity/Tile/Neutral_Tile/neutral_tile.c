#include <stdlib.h>

#include "conf.h"
#include "Game/Entity/Tile/Neutral_Tile/neutral_tile.h"
#include "Game/Entity/Tile/Neutral_Tile/_neutral_tile_render_grid_update.h"

Neutral_Tile* create_neutral_tile(
    Game_Clock* game_clock,
    Tiles_Data* tiles_data,
    Tile_Type type,
    Tile_Variation variation,
    tile_update_render_grid_cb* update_render_grid_cb
)
{
    Neutral_Tile* tile = (Neutral_Tile*)malloc(sizeof(Neutral_Tile));

    tile->type = type;
    tile->variation = variation;

    tile->count = 0;
    tile->positions = NULL;

    // Get the tile's animation.
    gather_tile_data(tiles_data, type, variation, NULL, NULL, &tile->animation);

    // Set the appropriate render grid update callback function
    // Use multi-layered cb if height of frame is that of two regular-sized frames
    if (tile->animation->frames->height == (DEFAULT_TILE_SIZE * 2)) {
        *update_render_grid_cb = update_multi_layered_tile_render_grid;
    } else {
        *update_render_grid_cb = update_regular_tile_render_grid;
    }

    return tile;
}
