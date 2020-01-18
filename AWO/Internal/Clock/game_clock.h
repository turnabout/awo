#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cJSON.h>

#include "Game_Data/Clock_Data/clock_data.h"

/*! @brief Main game clock used for updating and keeping animations synchronized.
 */
typedef struct Game_Clock Game_Clock;

typedef struct Tile Tile;

/*! @brief Creates the game clock along with its animation clocks.
 *
 *  @param[in] clock_data The clock data module describing the game's clocks.
 *  @return The created game clock object.
 */
Game_Clock* create_game_clock(Clock_Data* clock_data);

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
 *  @param[in] clock_index Index of the animation clock the tile should subscribe to.
 *  @param[in] sub_clock_index Index of the animation sub-clock the tile should subscribe to.
 */
void register_game_clock_tile(
    Game_Clock* game_clock, 
    Tile* tile,
    Clock_Index clock_index
);

void unregister_game_clock_tile(
    Game_Clock* game_clock,
    Tile* tile,
    Clock_Index clock_index
);

/*! @brief Frees the game clock's allocated memory.
 *
 *  @param[in] game_clock The game clock.
 */
void free_game_clock(Game_Clock* clock);