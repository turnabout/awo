#pragma once

#include "definitions.h"
#include "game_state_update.h"

/*! @brief Creates the game instance.
 *
 *  @param[in] window_width The window's initial tiles_width, in pixels.
 *  @param[in] window_height The window's initial tiles_height, in pixels.
 *  @return The created game instance with state of `Game_Initialized`, NULL if an error occurred.
 */
AWO* create_game(int window_width, int window_height);

/*! @brief Direct reference to the game loop.
 *
 * @note Ensure the game's state is `GamePrepared` before running.
 *
 *  @param[in] game The game, typecasted to void*.
 */
void game_loop(void* game);