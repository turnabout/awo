#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cJSON.h>

#include "Game/Renderer/game_renderer.h"
#include "Game/Data/Clock/clock_data.h"

/*! @brief Main game clock used for updating and keeping animations synchronized.
 */
typedef struct Game_Clock Game_Clock;

typedef struct Tile Tile;

/*! @brief Creates the game clock along with its animation clocks.
 *
 *  @note Call `activate_game_clock_subscribers` before using ingame.
 *
 *  @param[in] clock_data_cJSON JSON describing the game clock and its animation clocks.
 *  @return The created game clock object.
 */
Game_Clock* create_game_clock(cJSON* clock_data_JSON);

/*! @brief Activates the game clock's subscriber modules, getting it ready for ingame usage.
 *
 *  @param[in] game_clock The game clock module.
 *  @param[in] game_renderer The game renderer module.
 *  @param[in] game_palette Reference to the game's palette object ID.
 */
void activate_game_clock_subscribers(
    Game_Clock* game_clock,
    Game_Renderer* game_renderer,
    GLuint* game_palette
);

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
    Animation_Clock_Index clock_index,
    Animation_Sub_Clock_Index sub_clock_index
);

void unregister_game_clock_tile(
    Game_Clock* game_clock,
    Tile* tile,
    Animation_Clock_Index clock_index,
    Animation_Sub_Clock_Index sub_clock_index
);

/*! @brief Frees the game clock's allocated memory.
 *
 *  @param[in] game_clock The game clock.
 */
void free_game_clock(Game_Clock* clock);