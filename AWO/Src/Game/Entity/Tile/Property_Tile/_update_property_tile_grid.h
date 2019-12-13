#pragma once


#include "Game/Entity/Tile/tile.h"
#include "Game/Entity/Tile/Property_Tile/property_tile.h"

/*! @brief Updates parts of the render grid occupied by the given tile.
 *
 *  @param[in] tile The tile.
 *  @param[in] animation_index The index of the animation frame used to updated the render grid.
 */
void update_regular_property_render_grid(Tile* tile, Uint8 animation_index);

/*! @brief Updates parts of the render grid occupied by the given multi-layered tile.
 *
 * For base tiles.
 *
 *  @param[in] tile The tile.
 *  @param[in] animation_index The index of the animation frame used to updated the render grid.
 */
void update_base_render_grid(Tile* tile, Uint8 animation_index);
