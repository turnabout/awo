#pragma once

#include "../_tile_data.h"
#include "../Tile_Placement_Rule/tile_placement_rule.h"

/*! @brief Gets the tile placement rules for the given tile type.
 *
 *  @param[in] tile_data The tile data module.
 *  @param[in] type The type for which to get tile placement rules.
 *  @return Array of Tile_Placement_Rule pointers belonging to this tile type. NULL if count is 0.
 *  @return Object containing the Tile_Placement_Rule pointers belonging to this tile type. 
 *  NULL if none.
 */
Tile_Placement_Rule_Set* get_tile_placement_rules(Tile_Data* tile_data, Tile_Type type);