#pragma once

#include "./tile_type_data.h"

#include "../Tile_Variation_Data/tile_variation_data.h"
#include "../Tile_Auto_Var/tile_auto_var.h"
#include "../Tile_Placement_Rule/tile_placement_rule.h"

struct Tile_Type_Data {

    // Map holding every variation of this tile type's data (Tile_Variation_Data).
    map_t vars_map;

    // Amount of variations this tile type has.
    int var_count;

    // List of every variation this tile type has
    Tile_Variation* vars_list;

    // Amount of auto-vars this tile type has.
    int auto_vars_count;

    // List of auto-vars, used to automatically determine this tile's variation when placing it in
    // design room mode.
    Auto_Var_Data* auto_vars;

    // This tile's placement rules. Used to block the placement of this tile in design room mode
    // when surrounded by certain tiles.
    Tile_Placement_Rule_Set* placement_rules;

};