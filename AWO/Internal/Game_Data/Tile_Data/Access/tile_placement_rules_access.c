#include "Game/Data/Tile/_tiles_data.h"

Tile_Placement_Rule_Set* get_tile_placement_rules(Tiles_Data* tiles_data, Tile_Type type)
{
    return tiles_data->neutral_tiles->src[type]->placement_rules;
}
