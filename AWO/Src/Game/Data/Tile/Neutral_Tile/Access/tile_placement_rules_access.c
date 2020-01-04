#include "Game/Data/Tile/_tiles_data.h"

Tile_Placement_Rule** get_tile_placement_rules(Tiles_Data* tiles_data, Tile_Type type, int* count)
{
    *count = tiles_data->neutral_tiles->src[type]->placement_rule_count;
    return tiles_data->neutral_tiles->src[type]->placement_rules;
}
