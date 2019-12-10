#pragma once

#include "Game/Data/Tile/Neutral_Tile/Type/_tile_type_data.h"
#include "Game/Data/Tile/Neutral_Tile/Type/Variation/_tile_variation_data.h"
#include "Game/Data/Tile/Neutral_Tile/neutral_tiles_data.h"

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
    Tiles_Data* tiles_data,
    Tile_Type type,
    Tile_Variation variation
);
