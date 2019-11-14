#pragma once

#include "Game/Entity/Tile/tile.h"

/*! @brief Tiles clock subscriber module.
 *  
 * This module subscribes to the game clock, receiving all tick events emitted by it.
 * The module processes those tick events and keeps game entities' animations up-to-date.
 */
typedef struct Tiles_Clock_Subscriber Tiles_Clock_Subscriber;

/*! @brief Creates the tiles clock subscriber module.
 *  
 *  @return The created module.
 */
Tiles_Clock_Subscriber* create_tiles_clock_subscriber();

/*! @brief Registers the given tile with the subscriber module.
 *
 * This ensures the tile's animation index will properly remain updated.
 *  
 *  @param[in] subscriber_module The subscriber module.
 *  @param[in] tile The tile to register with the module.
 */
void register_tiles_clock_subscriber_tile(Tiles_Clock_Subscriber* subscriber_module, Tile* tile);

/*! @brief Processes the given list of tick events, updating entities registered with the module.
 *  
 *  @param[in] subscriber_module The subscriber module.
 *  @param[in] events_list The list of tick events to process.
 */
void process_tiles_tick_events(
    Tiles_Clock_Subscriber* subscriber_module, 
    Tick_Events_List* events_list
);

/*! @brief Frees the subscriber module.
 *  
 *  @param[in] subscriber_module The subscriber module.
 */
void free_tiles_clock_subscriber(Tiles_Clock_Subscriber* subscriber_module);
