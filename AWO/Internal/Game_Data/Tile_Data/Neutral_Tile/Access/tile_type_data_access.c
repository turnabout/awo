#include "Game/Data/Tile/_tiles_data.h"

Tile_Type get_next_basic_tile_type()
{
    static Tile_Type type = NEUTRAL_TILE_TYPE_BASIC_FIRST;

    // No more tile types to loop, reset index and return NULL to stop looping
    if (type == NEUTRAL_TILE_TYPE_BASIC_LAST) {
        type = NEUTRAL_TILE_TYPE_BASIC_FIRST;
        return TILE_TYPE_NONE;
    }

    return type++;
}
