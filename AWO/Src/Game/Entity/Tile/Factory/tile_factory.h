#pragma once

#include "Game/Clock/game_clock.h"
#include "Game/Data/Tile/tiles_data.h"
#include "Game/Entity/Tile/tile.h"
#include "Game/Clock/Clock_Subscriber/clock_subscriber.h"

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
 *  @param[in] tiles_clock_sub The tiles clock subscription module.
 */
Tile_Factory* create_tile_factory(
    Tiles_Data* tiles_data,
    Game_Clock* game_clock,
    Clock_Subscriber* tiles_clock_sub
);

/*! @brief Gets a tile.
 *
 *  @param[in] factory The tile factory object.
 *  @param[in] type The type of the tile to get.
 *  @param[in] variation The variation of the tile to get.
 */
Tile* get_tile_factory_tile(Tile_Factory* factory, Tile_Type type, Tile_Variation variation);

/*! @brief Frees memory taken up by tile factory.
 *
 *  @param[in] factory The tile factory object.
 */
void free_tile_factory(Tile_Factory* factory);