#pragma once

#include "types.h"

/*! @brief Callback function used by tiles when their animation updates.
 *
 *  Updates the render grid occupied by this tile.
 *
 *  @param[in] tile The tile whose corresponding render grid(s) pixels should be updated.
 *  @param[in] animation_index The animation index of the frame used to update the render grid.
 */
typedef void (*update_tile_animation_cb)(void* tile, Uint8 animation_index);

/*! @brief Callback function used by tiles to update themselves visually based on their fog status.
 *
 *  @param[in] tile The tile whose corresponding render grid(s) pixels should be updated.
 *  @param[in] fog Whether the tile is covered by fog.
 */
typedef void (*update_fog_status_cb)(void* tile, Bool fog);
