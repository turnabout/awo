#pragma once

#include "./tile_data.h"
#include "./Tile_Type_Data/_tile_type_data.h"
#include "./Tile_Variation_Data/_tile_variation_data.h"
#include "./Tile_Auto_Var/_tile_auto_var.h"
#include "./Tile_Placement_Rule/_tile_placement_rule.h"

struct Tile_Data {

    // Data for every tile type.
    Tile_Type_Data* src[NEUTRAL_TILE_TYPE_COUNT];

};