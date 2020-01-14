#pragma once

#include <cJSON.h>
#include <c_hashmap.h>

#include "Game_Data/Clock_Data/clock_data.h"
#include "Game_Data/Tile_Data/Headers/tile_types.h"
#include "Game_Data/Tile_Data/Headers/tile_variations.h"
#include "Game_Data/Tile_Data/Tile_Type_Data/Tile_Variation_Data/tile_variation_data.h"
#include "Game_Data/Tile_Data/Tile_Type_Data/Tile_Auto_Var/tile_auto_var.h"
#include "Game_Data/Tile_Data/Tile_Type_Data/Tile_Placement_Rule/tile_placement_rule.h"

// A single tile's visual data.
typedef struct Tile_Type_Data
{
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

} Tile_Type_Data;

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
