#pragma once

#include <cJSON.h>
#include <c_hashmap.h>

#include "Headers/tile_type_data.h"
#include "Headers/tile_types.h"
#include "Headers/tile_auto_var_access.h"
#include "Headers/tile_placement_rule_access.h"
#include "Headers/tile_variation_data_access.h"

#include "Game_Data/Tile_Data/Tile_Type_Data/Tile_Variation_Data/tile_variation_data.h"
#include "Game_Data/Tile_Data/Tile_Type_Data/Tile_Auto_Var/tile_auto_var.h"
#include "Game_Data/Tile_Data/Tile_Type_Data/Tile_Placement_Rule/tile_placement_rule.h"

/*! @brief Creates tile type data from the given JSON.
 *
 *  @param[in] tile_type_JSON The JSON object of this tile type.
 *  @param[in] variations_list_hashmap Hashmap containing every individual tile variation, with
 *  the keys as the corresponding variation short strings.
 *  @param[in] ss_width The tiles_width of the game's sprite sheet.
 *  @param[in] ss_height The tiles_height of the game's sprite sheet.
 *  @return The created tile variation data object.
 */
Tile_Type_Data* create_tile_type_data(
    cJSON* tile_type_JSON, 
    map_t variations_list_hashmap,
    int ss_width,
    int ss_height
);

/*! @brief Frees all data used up by the given tile type data object.
 *
 *  @param[in] tile_type_data The tile type data object to free.
 */
void free_tile_type_data(Tile_Type_Data* tile_type_data);
