#pragma once

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
    Tiles_List* tiles_list[ANIMATION_CLOCK_COUNT][MINIMAL_ANIMATION_SUB_CLOCK_COUNT];

    // Reference to the game's tiles data object.
    Tiles_Data* tiles_data;

    // Reference to the game clock publisher's tick events list.
    Tick_Events_List* tick_events;

} Game_Clock_Tile_Subscriber;

/*! @brief Creates the clock subscriber module.
 *  
 *  @param[in] tiles_data Pointer to the game's tiles data object.
 *  @param[in] tick_events Pointer to the game clock publisher's tick events list.
 *  @return The created module.
 */
Game_Clock_Tile_Subscriber* create_game_clock_tile_subscriber(
    Tiles_Data* tiles_data,
    Tick_Events_List* tick_events
);

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

/*! @brief Update entities registered with the module, processing current tick events.
 *  
 *  @param[in] clock_subscriber The clock subscriber module.
 */
void update_game_clock_tile_subscriber(Game_Clock_Tile_Subscriber* clock_subscriber);

/*! @brief Frees the subscriber module.
 *  
 *  @param[in] clock_subscriber The clock subscriber module.
 */
void free_game_clock_tile_subscriber(Game_Clock_Tile_Subscriber* clock_subscriber);
