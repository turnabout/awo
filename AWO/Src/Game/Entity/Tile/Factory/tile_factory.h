#pragma once

#include "Game/Clock/game_clock.h"
#include "Game/Data/Tile/tiles_data.h"
#include "Game/Entity/Tile/tile.h"

/*! @brief Object used to create tiles.
 *
 * Can be used as an abstract interface to get the pointer to a tile of the requested type and
 * variation, without worrying about how it was created or its internal details.
 */
typedef struct Tile_Factory Tile_Factory;

/*! @brief Creates a tile factory.
 *
 *  @param[in] tiles_data The tiles data object.
 *  @param[in] game_clock The game clock object.
 */
Tile_Factory* TF_create(Tiles_Data* tiles_data, Game_Clock* game_clock);

/*! @brief Gets a tile.
 *
 *  @param[in] factory The tile factory object.
 *  @param[in] type The type of the tile to get.
 *  @param[in] variation The variation of the tile to get.
 */
Tile* TF_get_tile(Tile_Factory* factory, Tile_Type type, Tile_Variation variation);