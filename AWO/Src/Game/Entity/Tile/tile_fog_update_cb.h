#pragma once

#include "types.h"

/*! @brief Callback function used by tiles to update themselves visually based on their fog status.
 *
 *  @param[in] tile The tile whose corresponding render grid(s) pixels should be updated.
 *  @param[in] fog Whether the tile is covered by fog.
 */
typedef void (*fog_update_cb)(void* tile, Bool fog);
