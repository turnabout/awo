#pragma once

#include "Game/Entity/Tile/tile.h"
#include "Game/Entity/Tile/tile_render_grid_update.h"

/*! @brief Updates parts of the render grid occupied by the given tile.
 *
 * For regular-sized tiles.
 *
 *  @param[in] tile The tile.
 *  @param[in] animation_index The index of the animation frame used to updated the render grid.
 */
void update_regular_tile_render_grid(Tile* tile, Uint8 animation_index);

/*! @brief Updates parts of the render grid occupied by the given multi-layered tile.
 *
 * For tiles that are two tiles high.
 *
 *  @param[in] tile The tile.
 *  @param[in] animation_index The index of the animation frame used to updated the render grid.
 */
void update_multi_layered_tile_render_grid(Tile* tile, Uint8 animation_index);
