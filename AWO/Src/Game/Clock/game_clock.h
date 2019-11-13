#pragma once

#include <cJSON.h>

#include "Game/Clock/Animation_Clock/enums.h"
#include "Game/Clock/Animation_Clock/tick_event.h"

/*! @brief Main game clock used for updating and keeping animations synchronized.
 */
typedef struct Game_Clock Game_Clock;

/*! @brief Creates the game clock along with its animation clocks.
 *
 *  @param[in] clock_data_cJSON The data JSON object describing the game clock and its animation 
 *  clocks.
 *  @param[in] delta_time Time elapsed since the last game frame.
 */
Game_Clock* create_game_clock(const cJSON* clock_data_JSON);

/*! @brief Keeps the game clock's current tick updated, along with its animation clocks.
 *
 *  @param[in] game_clock The game clock.
 *  @param[in] delta_time Time elapsed since the last game frame.
 */
void update_game_clock(Game_Clock* game_clock, float delta_time);

Tick_Events_List* get_game_clock_tick_event_list(Game_Clock* game_clock);

#ifdef _DEBUG
/*! @brief Prints the contents of the given list of tick events.
 *
 *  @param[in] game_clock The game clock.
 */
void print_tick_event_list(Tick_Events_List* tick_events);
#endif

/*! @brief Frees the game clock's allocated memory.
 *
 *  @param[in] game_clock The game clock.
 */
void free_game_clock(Game_Clock* clock);