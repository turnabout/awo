#pragma once

/*! @brief Callback function used by tiles to update the render grid.
 *
 *  @param[in] tile The tile whose corresponding render grid(s) pixels should be updated.
 *  @param[in] animation_index The animation index of the frame used to update the render grid.
 */
typedef void (*tile_update_render_grid_cb)();
