#pragma once

#include <cjson/cJSON.h>
#include <hashmap/hashmap.h>

#include "Game_Data/Tile_Data/Tile_Variation_Data/tile_variation_data.h"

typedef struct Auto_Var_Data Auto_Var_Data;

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
