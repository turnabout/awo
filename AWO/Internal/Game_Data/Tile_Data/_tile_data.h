#pragma once

#include "Game_Data/Tile_Data/tile_data.h"
#include "Game_Data/Tile_Data/Tile_Type_Data/tile_type_data.h"
#include "Game_Data/Tile_Data/Tile_Type_Data/Tile_Variation_Data/tile_variation_data.h"
#include "Game_Data/Tile_Data/Tile_Type_Data/Tile_Auto_Var/tile_auto_var.h"
#include "Game_Data/Tile_Data/Tile_Type_Data/Tile_Placement_Rule/tile_placement_rule.h"

struct Neutral_Tiles_Data
{
    Tile_Type_Data* src[NEUTRAL_TILE_TYPE_COUNT];
};

/*! @brief Gets the tile variation data object for the given type and variation.
 *
 *  @param[in] tiles_data The tiles data object.
 *  @param[in] type The tile's type.
 *  @param[in] variation The tile's variation.
 *  @return The corresponding tile variation data object, or NULL if none was found.
 */
Tile_Variation_Data* get_tile_variation_data(
    Neutral_Tiles_Data* tiles_data,
    Tile_Type type,
    Tile_Variation variation
);
