#pragma once

#include "Game_Data/Tile_Data/Tile_Type_Data/tile_type_data.h"
#include "Game_Data/Tile_Data/Tile_Type_Data/Tile_Variation_Data/tile_variation_data.h"
#include "Game_Data/Tile_Data/Tile_Type_Data/Tile_Placement_Rule/tile_placement_rule.h"

/*! @brief Gets the tile placement rules for the given tile type.
 *
 *  @param[in] tile_type_data The tile type's data object.
 *  @return Array of Tile_Placement_Rule pointers belonging to this tile type. NULL if count is 0.
 */
Tile_Placement_Rule_Set* get_tile_placement_rules(Tile_Type_Data* tile_type_data);