#include "Game_Data/Tile_Data/Tile_Type_Data/_tile_type_data.h"

Tile_Placement_Rule_Set* get_tile_placement_rules(Tile_Type_Data* tile_type_data)
{
    return tile_type_data->placement_rules;
}
