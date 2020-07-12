#pragma once

#include <cjson/cJSON.h>

#include "AWO/game_data.h"

#include "Headers/macros.h"
#include "Headers/tile_auto_var_access.h"
#include "Headers/tile_placement_rule_access.h"
#include "Headers/tile_variation_data_access.h"

/*! @brief Creates the tile data module.
 *
 *  @param[in] tiles_data_JSON The JSON describing tile data.
 *  @param[in] ss_width The width of the game's sprite sheet.
 *  @param[in] ss_height The height of the game's sprite sheet.
 *  @return The generated tile data object.
 */
Tile_Data* create_tile_data(cJSON* tiles_data_JSON, int ss_width, int ss_height);

/*! @brief Frees all memory occupied by the tile data module.
 *
 *  @param[in] tiles_data The tiles data object.
 */
void free_tile_data(Tile_Data* tiles_data);
