#pragma once

#include "../Tile_Type_Data/tile_type_data.h"
#include "../Tile_Variation_Data/tile_variation_data.h"

/*! @brief Gets the variation a tile type should have when surrounded with given adjacent tiles.
 *
 *  @param[in] tile_data The tile data object.
 *  @param[in] middle_tile The middle tile surrounded by the other given tiles.
 *  @param[in] top_tile The top adjacent tile.
 *  @param[in] right_tile The right adjacent tile.
 *  @param[in] bottom_tile The bottom adjacent tile.
 *  @param[in] left_tile The left adjacent tile.
 *  @return The generated auto tile_var.
 */
Tile_Variation get_tile_auto_var(
    Tile_Data* tile_data,
    Tile_Type middle_tile,
    Tile_Type top_tile,
    Tile_Type right_tile,
    Tile_Type bottom_tile,
    Tile_Type left_tile
);
