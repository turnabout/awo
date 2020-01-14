#pragma once

#include "Game_Data/Tile_Data/Tile_Type_Data/tile_type_data.h"
#include "Game_Data/Tile_Data/Tile_Type_Data/Tile_Variation_Data/tile_variation_data.h"

/*! @brief Gets the default tile variation for a tile type.
 *
 *  @param[in] tile_type_data The data object of the tile type.
 *  @return The default tile variation for the given tile type.
 */
Tile_Variation get_default_tile_variation(Tile_Type_Data* tile_type_data);

/*! @brief Gets the the tile variation data object corresponding to a tile variation.
 *
 *  @param[in] tile_type_data The data object of the tile type from which to get the tile var data.
 *  @param[in] var The tile variation for which to get the data.
 *  @return The fetched tile variation data object, or NULL if it doesn't exist.
 */
Tile_Variation_Data* get_tile_variation_data(Tile_Type_Data* tile_type_data, Tile_Variation var);

/*! @brief Gets the next tile variation belonging to the given tile type.
 *  Must be called continuously until it returns NULL.
 *  Goes through all tile variations of the tile type until all have been returned.
 *
 *  @param[in] tile_type_data The data object of the tile type.
 *  @return The next tile variation belonging to this tile type or TILE_VAR_NONE if the tile
 *  type has no more variations.
 */
Tile_Variation get_next_tile_variation(Tile_Type_Data* tile_type_data);

/*! @brief Gets the next tile variation animation for the given tile type data.
 *  Must be called continuously until it returns NULL.
 *  Goes through all tile variations of the tile type until all have been returned.
 *
 *  @param[in] tile_type_data The data object of the tile type.
 *  @return The next tile's variation data object or NULL if the tile has no more variations.
 */
Tile_Variation_Data* get_next_tile_variation_data(Tile_Type_Data* tile_type_data);

/*! @brief Gets whether a tile variation exists on the given tile type data.
 *
 *  @param[in] tile_type_data The data object of the tile type.
 *  @param[in] var The tile variation to check.
 *  @return TRUE if it exists, FALSE if it doesn't.
 */
Bool tile_type_variation_exists(Tile_Type_Data* tile_type_data, Tile_Variation var);