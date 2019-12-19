#include "Game/Entity/Tile/Neutral/_neutral_tile.h"

void delete_neutral_tile(
    Game_Renderer* game_renderer,
    Game_Clock* game_clock,
    void* tile_arg,
    void* tiles_data
)
{
    if (tile_arg == NULL) {
        return;
    }

    Neutral_Tile* tile = tile_arg;

    // Get the tile's animation data & attempt to register it with the game clock module.
    Animation_Clock_Index clock_index;
    Animation_Sub_Clock_Index sub_clock_index;

    gather_tile_data(tiles_data, tile->type, tile->variation, &clock_index, &sub_clock_index, NULL);
    unregister_game_clock_tile(game_clock, tile_arg, clock_index, sub_clock_index);

    // Clear the top render grid tile layer of taller tiles
    if (tile->animation->frames->height == (DEFAULT_TILE_SIZE * 2)) {
        clear_tile_layers_pixel(game_renderer, tile->x, tile->y);
    }

    free(tile);
}
