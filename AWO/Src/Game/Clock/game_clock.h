#pragma once

#include <cJSON.h>

#include "Game/Clock/enums.h"
#include "Game/Clock/Tick_Event/tick_event.h"

/*! @brief Main game clock used for updating and keeping animations synchronized.
 */
typedef struct Game_Clock Game_Clock;

typedef struct Tiles_Data Tiles_Data;
typedef struct Tile Tile;

/*! @brief Creates the game clock along with its animation clocks.
 *
 *  @param[in] clock_data_cJSON JSON describing the game clock and its animation clocks.
 *  @param[in] tiles_data The game's tiles data object.
 *  @return The created game clock object.
 */
Game_Clock* create_game_clock(const cJSON* clock_data_JSON, Tiles_Data* tiles_data);

/*! @brief Keeps the game clock's current tick updated, along with its animation clocks.
 *
 *  @param[in] game_clock The game clock.
 *  @param[in] delta_time Time elapsed since the last game frame.
 */
void update_game_clock(Game_Clock* game_clock, float delta_time);

/*! @brief Registers the given tile with the game clock module to keep its animation updated.
 *
 *  @param[in] game_clock The game clock.
 *  @param[in] tile The tile object.
 */
void register_game_clock_tile(Game_Clock* game_clock, Tile* tile);

/*! @brief Frees the game clock's allocated memory.
 *
 *  @param[in] game_clock The game clock.
 */
void free_game_clock(Game_Clock* clock);