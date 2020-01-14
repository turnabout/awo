#pragma once

#include <cJSON.h>
#include <c_hashmap.h>

#include "Game_Data/Tile_Data/Tile_Type_Data/Tile_Variation_Data/tile_variation_data.h"

typedef struct Auto_Var_Data
{

    // The variation selected by this auto-var.
    Tile_Variation tile_var;

    // Array listing the acceptable adjacent tiles for this auto-var to be selected.
    int adjacent_tiles[4];

} Auto_Var_Data;

typedef enum Auto_Var_Adjacent_Tile {
    Auto_Var_Up    = 0,
    Auto_Var_Right = 1,
    Auto_Var_Down  = 2,
    Auto_Var_Left  = 3,
} Auto_Var_Adjacent_Tile;

/*! @brief Creates a list of tile auto var data objects.
 *
 *  @param[in] auto_var_JSON The JSON object describing this auto var.
 *  @param[in] variations_list_hashmap Hashmap containing every individual tile variation.
 *  @param[out] auto_vars_amount The amount of auto vars generated.
 *  @return The created auto var data objects.
 */
Auto_Var_Data* create_tile_auto_var_data(
    cJSON* auto_var_JSON,
    map_t* variations_list_hashmap,
    int* auto_vars_amount
);
