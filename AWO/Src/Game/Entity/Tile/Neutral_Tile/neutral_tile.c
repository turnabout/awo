#include <stdlib.h>

#include "Game/Entity/Tile/Neutral_Tile/neutral_tile.h"

Neutral_Tile* create_neutral_tile(
    Game_Clock* game_clock,
    Neutral_Tiles_Data* tiles_data,
    Tile_Type type,
    Tile_Variation variation
)
{
    Neutral_Tile* neutral_tile = (Neutral_Tile*)malloc(sizeof(Neutral_Tile));

    neutral_tile->type = type;
    neutral_tile->variation = variation;

    neutral_tile->count = 0;
    neutral_tile->positions = NULL;

    return neutral_tile;
}
