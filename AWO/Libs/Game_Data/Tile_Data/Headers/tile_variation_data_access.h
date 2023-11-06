#pragma once

// Libs
#include "../../Tile_Data/Tile_Type_Data/tile_type_data.h"
#include "../../Tile_Data/Tile_Variation_Data/tile_variation_data.h"
#include "../../Clock_Data/clock_data.h"
#include "../../Animation/animation.h"

/*! @brief Gathers data from the given tile type/variation combination.
 *
 *  @param[in] tile_data The tile data module.
 *  @param[in] type The tile type.
 *  @param[in] var The tile variation.
 *  @param[out] clock Filled with the type/variation combination clock. NULL if invalid.
 *  @param[out] animation Filled with the type/variation combination animation. NULL if invalid.
 */
void gather_tile_data(
    Tile_Data* tile_data,
    Tile_Type type,
    Tile_Variation var,
    Clock_Index* clock,
    Animation** animation
);

/*! @brief Gets the next tile variation belonging to the given tile type.
 *
 *  @note Must be called continuously until it returns NULL. Goes through all tile variations of 
 *  the tile type until all have been returned.
 *
 *  @param[in] tile_data The tile data module.
 *  @param[in] type The tile type.
 *  @return The next tile variation belonging to this tile type or TILE_VAR_NONE if the tile
 *  type has no more variations.
 */
Tile_Variation get_next_tile_variation(Tile_Data* tile_data, Tile_Type type);

/*! @brief Gets the default tile variation for a tile type.
 *
 *  @param[in] tile_data The tile data module.
 *  @param[in] type The tile type.
 *  @return The default tile variation for the given tile type.
 */
Tile_Variation get_default_tile_variation(Tile_Data* tile_data, Tile_Type type);

/*! @brief Gets whether a tile type/variation combination exists.
 *
 *  @param[in] tile_data The tile data module.
 *  @param[in] type The tile type.
 *  @param[in] var The tile variation to check.
 *  @return TRUE if it exists, FALSE if it doesn't.
 */
Bool tile_type_variation_exists(Tile_Data* tile_data, Tile_Type type, Tile_Variation var);