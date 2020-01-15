#pragma once

#include "Game_Data/Tile_Data/tile_data.h"
#include "Game_Data/Tile_Data/Tile_Type_Data/_tile_type_data.h"
#include "Game_Data/Tile_Data/Tile_Variation_Data/_tile_variation_data.h"
#include "Game_Data/Tile_Data/Tile_Auto_Var/_tile_auto_var.h"
#include "Game_Data/Tile_Data/Tile_Placement_Rule/_tile_placement_rule.h"

struct Tile_Data {

    // Data for every tile type.
    Tile_Type_Data* src[NEUTRAL_TILE_TYPE_COUNT];

};