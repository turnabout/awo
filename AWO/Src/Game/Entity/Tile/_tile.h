#pragma once

#include "Game/Entity/Tile/tile.h"

/*! @brief Callback function used by tiles to update the render grid.
 *
 *  @param[in] tile The tile whose corresponding render grid(s) pixels should be updated.
 *  @param[in] animation_index The tile whose corresponding render grid(s) pixels should be updated.
 */
typedef void (*update_tile_render_grid_cb)();

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
 * For tiles that are two-tiles high.
 *
 *  @param[in] tile The tile.
 *  @param[in] animation_index The index of the animation frame used to updated the render grid.
 */
void update_multi_layered_tile_render_grid(Tile* tile, Uint8 animation_index);