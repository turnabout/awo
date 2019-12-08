#pragma once

#include "Game/Entity/Tile/tile.h"
#include "Game/Entity/Tile/tile_update_cb.h"

/*! @brief Updates the palette index this tile used based on given fog status.
 *
 * For regular-sized tiles.
 *
 *  @param[in] tile The tile.
 *  @param[in] fog Whether this tile is foggy or not.
 */
void update_regular_property_fog_status(void* tile, Bool fog);

/*! @brief Updates the palette index this tile used based on given fog status.
 *
 * Specifically for base tiles.
 *
 *  @param[in] tile The tile.
 *  @param[in] fog Whether this tile is foggy or not.
 */
void update_base_fog_status(void* tile, Bool fog);
