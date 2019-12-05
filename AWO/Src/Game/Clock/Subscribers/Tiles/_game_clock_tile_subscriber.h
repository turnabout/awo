#pragma once

#include "Utilities/Linked_List/linked_list.h"
#include "Game/Entity/Tile/tile.h"

typedef struct Tiles_List {

    // How many tiles belong to the list.
    int tiles_count;

    // Tiles belonging to the list.
    Tile** tiles;

} Tiles_List;

/*! @brief Clock subscriber module.
 *  
 * This module subscribes to the game clock, receiving all tick events emitted by it.
 * The module processes those tick events and keeps game entities' animations up-to-date.
 */
typedef struct Game_Clock_Tile_Subscriber {

    // List of every tile, sorted by which animation clock/sub-clocks they belong to.
    Tiles_List* tiles_list[ANIMATION_CLOCK_COUNT][MAX_ANIMATION_SUB_CLOCK_COUNT];

    // List of every tile registered, sorted by which animation clock/sub-clocks they belong to.
    Linked_List* tiles_lists[ANIMATION_CLOCK_COUNT][MAX_ANIMATION_SUB_CLOCK_COUNT];

    // Reference to the game clock publisher's tick events list.
    Tick_Events_List* tick_events;

} Game_Clock_Tile_Subscriber;

/*! @brief Creates the clock subscriber module.
 *  
 *  @return The created module.
 */
Game_Clock_Tile_Subscriber* create_game_clock_tile_subscriber();

/*! @brief Registers the given tile with the subscriber module.
 *
 * This ensures the tile's animation index will properly remain updated.
 *  
 *  @param[in] clock_subscriber The clock subscriber module.
 *  @param[in] tile The tile to register with the module.
 *  @param[in] clock_index Index of the animation clock the tile should subscribe to.
 *  @param[in] sub_clock_index Index of the animation sub-clock the tile should subscribe to.
 */
void register_clock_subscriber_tile(
    Game_Clock_Tile_Subscriber* module,
    Tile* tile,
    Animation_Clock_Index clock_index,
    Animation_Sub_Clock_Index sub_clock_index
);

void unregister_clock_subscriber_tile(
    Game_Clock_Tile_Subscriber* module,
    Tile* tile,
    Animation_Clock_Index clock_index,
    Animation_Sub_Clock_Index sub_clock_index
);

/*! @brief Processes a tick event destined to the tile subscriber clock.
 *  
 *  @param[in] tick_event The tick event received.
 *  @param[in] tile_subscriber_module The game clock tile subscriber module.
 */
void process_tile_subscriber_event(Tick_Event* tick_event, void* tile_subscriber_module);

/*! @brief Frees the subscriber module.
 *  
 *  @param[in] clock_subscriber The clock subscriber module.
 */
void free_game_clock_tile_subscriber(Game_Clock_Tile_Subscriber* clock_subscriber);
