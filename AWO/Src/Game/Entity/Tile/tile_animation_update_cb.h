#pragma once

#include "types.h"

/*! @brief Callback function used by tiles when their animation updates.
 *
 *  Updates the render grid occupied by this tile.
 *
 *  @param[in] tile The tile whose corresponding render grid(s) pixels should be updated.
 *  @param[in] animation_index The animation index of the frame used to update the render grid.
 */
typedef void (*tile_animation_update_cb)(void* tile, Uint8 animation_index);
