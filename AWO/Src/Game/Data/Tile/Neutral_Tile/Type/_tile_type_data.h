#pragma once

#include <cJSON.h>
#include <c_hashmap.h>
#include <cglm/types.h>

#include "Game/Data/Tile/Neutral_Tile/Type/Auto_Var/_tile_auto_var_data.h"
#include "Game/Data/Tile/enums.h"
#include "Game/Data/Clock/clock_data.h"

// A single tile's visual data.
typedef struct Tile_Type_Data
{
    map_t vars_map;              // Map holding every variation (Tile_Variation_Data)

    int vars_count;              // How many variations this tile has
    Tile_Variation* vars_list;   // List of every variation this tile has

    int auto_vars_count;         // Amount of auto vars_map this tile has
    Auto_Var_Data* auto_vars;         // List of auto vars_map used to autoselect this tile's variation 
                                 // when placing it in editor mode.

    Animation_Clock_Index clock; // Clock used by this tile to update its animation
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
