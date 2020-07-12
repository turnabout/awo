#pragma once

#include <cjson/cJSON.h>
#include <hashmap/hashmap.h>

#include "AWO/game_data.h"

/*! @brief A single tile type's visual data.
 */
typedef struct Tile_Type_Data Tile_Type_Data;

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
