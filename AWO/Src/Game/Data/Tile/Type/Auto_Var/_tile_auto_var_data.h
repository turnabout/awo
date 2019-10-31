#pragma once

#include <cJSON.h>
#include <c_hashmap.h>

#include "Game/Data/Tile/enums.h"

typedef struct Auto_Var
{
    Tile_Variation tile_var; // The variation selected by this auto tile_var
    int adjacent_tiles[4];   // Array pointing out which adjacent tiles are acceptable for this 
                             // auto tile_var to be selected.
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
