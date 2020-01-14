#pragma once

#include <cJSON.h>

#include "Game_Data/Tile_Data/Neutral_Tile/neutral_tiles_data.h"
#include "Game_Data/Tile_Data/Property_Tile/property_tiles_data.h"

typedef struct Tiles_Data Tiles_Data;

/*! @brief Creates the tiles data object.
 *
 *  @param[in] tiles_data_JSON The JSON describing the tiles' data.
 *  @param[in] ss_width The tiles_width of the game's sprite sheet.
 *  @param[in] ss_height The tiles_height of the game's sprite sheet.
 *  @return The generated tiles data object.
 */
Tiles_Data* create_tiles_data(
    cJSON* neutral_tiles_JSON,
    cJSON* property_tiles_JSON,
    int ss_width,
    int ss_height
);