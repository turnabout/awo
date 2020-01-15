#include "Game_Data/Tile_Data/_tile_data.h"

Tile_Placement_Rule_Set* get_tile_placement_rules(Tile_Data* tile_data, Tile_Type type)
{
    return tile_data->src[type]->placement_rules;
}
