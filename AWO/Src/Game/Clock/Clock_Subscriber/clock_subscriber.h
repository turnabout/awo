#pragma once

#include "Game/Entity/Tile/tile.h"

/*! @brief Clock subscriber module.
 *  
 * This module subscribes to the game clock, receiving all tick events emitted by it.
 * The module processes those tick events and keeps game entities' animations up-to-date.
 */
typedef struct Clock_Subscriber Clock_Subscriber;

/*! @brief Creates the clock subscriber module.
 *  
 *  @param[in] tiles_data Pointer to the game's tiles data object.
 *  @return The created module.
 */
Clock_Subscriber* create_clock_subscriber(Tiles_Data* tiles_data);

/*! @brief Registers the given tile with the subscriber module.
 *
 * This ensures the tile's animation index will properly remain updated.
 *  
 *  @param[in] clock_subscriber The clock subscriber module.
 *  @param[in] tile The tile to register with the module.
 */
void register_clock_subscriber_tile(Clock_Subscriber* clock_subscriber, Tile* tile);

/*! @brief Processes the given list of tick events, updating entities registered with the module.
 *  
 *  @param[in] clock_subscriber The clock subscriber module.
 *  @param[in] events_list The list of tick events to process.
 */
void process_tick_events(Clock_Subscriber* clock_subscriber, Tick_Events_List* events_list);

/*! @brief Frees the subscriber module.
 *  
 *  @param[in] subscriber_module The subscriber module.
 */
void free_tiles_clock_subscriber(Clock_Subscriber* subscriber_module);
