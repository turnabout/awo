#pragma once

#include "Game_Data/Tile_Data/Tile_Type_Data/Tile_Placement_Rule/tile_placement_rule.h"

/*! @brief Creates a tile placement rule.
 *
 *  @param[in] JSON The JSON object representing this tile placement rule.
 *  @return The allocated tile placement rule.
 */
Tile_Placement_Rule* create_tile_placement_rule(cJSON* JSON);

/*! @brief Frees an allocated tile placement rule.
 *
 *  @param[in] rule The rule to free.
 */
void free_tile_placement_rule(Tile_Placement_Rule* rule);