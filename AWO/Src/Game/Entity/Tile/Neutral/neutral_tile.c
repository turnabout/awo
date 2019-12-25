#include <stdlib.h>

#include "Game/Entity/Tile/Neutral/_neutral_tile.h"

Neutral_Tile* create_neutral_tile(
    Game_Clock* game_clock,
    Tiles_Data* tiles_data,
    Tile_Type type,
    Tile_Variation variation,
    Uint8 x,
    Uint8 y
)
{
    Neutral_Tile* tile = malloc(sizeof(Neutral_Tile));

    tile->type = type;
    tile->variation = variation;
    tile->x = x;
    tile->y = y;
    tile->delete = delete_neutral_tile;

    // Get the tile's animation data & attempt to register it with the game clock module.
    // Animation_Clock_Index clock_index;

    gather_tile_data(tiles_data, type, variation, NULL, &tile->animation);
    // register_game_clock_tile(game_clock, (Tile*)tile, clock_index);

    // Set the appropriate render grid update callback function
    // Use tall tile cb if height of frame is that of two regular-sized frames
    if (tile->animation->frames->height == (DEFAULT_ENTITY_SIZE * 2)) {
        tile->update_grid = update_tall_tile_render_grid;
        tile->update_palette = update_tall_tile_palette;
    } else {
        tile->update_grid = update_tile_render_grid;
        tile->update_palette = update_tile_palette;
    }

    return tile;
}

void edit_neutral_tile_variation(
    Neutral_Tile* tile, 
    Game_Clock* game_clock, 
    Tiles_Data* tiles_data,
    Tile_Variation new_variation
)
{
    // Unregister the old tile's variation from the game clock 
    // Animation_Clock_Index clock_index;

    // gather_tile_data(tiles_data, tile->type, tile->variation, NULL);
    // unregister_game_clock_tile(game_clock, (Tile*)tile, clock_index);

    // Set the new variation and register the tile w/ its updated variation with the game clock
    tile->variation = new_variation;
    // gather_tile_data(tiles_data, tile->type, tile->variation, &tile->animation);
    // register_game_clock_tile(game_clock, (Tile*)tile, clock_index);
}
