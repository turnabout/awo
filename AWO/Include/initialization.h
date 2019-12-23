#pragma once

#include "definitions.h"

/*! @brief Creates the game instance.
 *
 *  @param[in] window_width The window's initial tiles_width, in pixels.
 *  @param[in] window_height The window's initial tiles_height, in pixels.
 *  @return The created game instance with state of `Game_Initialized`, NULL if an error occurred.
 */
AWO* create_game(int window_width, int window_height);

/*! @brief Prepares game for "design room" (stage editor) mode.
 *
 *  @note Expects game state to be `Game_Initialized`.
 *  @note Sets game state to `Game_Prepared`.
 *
 *  @param[in] game The game.
 *  @return 1 if the game was successfully prepared, 0 if an error occurred.
 */
int prepare_design_room_game(AWO* game);

/*! @brief Runs the main game loop.
 *
 *  @note Expects game state to be `Game_Prepared`.
 *  @note Sets game state to `Game_Running`.
 *
 *  @param[in] game The game.
 */
void run_game(AWO* game);

/*! @brief Stops the game from running.
 *
 *  @note Expects game state to be `Game_Running`.
 *  @note Sets game state to `Game_Initialized`.
 *
 *  @param[in] game The game.
 */
void stop_game(AWO* game);

/*! @brief Direct reference to the game loop.
 *
 * @note Ensure the game's state is `GamePrepared` before running.
 *
 *  @param[in] game The game, typecasted to void*.
 */
void game_loop(void* game);

/*! @brief Frees all resources taken up by the game and kills it.
 *
 *  @note Expects game state to be `Game_Initialized`.
 *
 *  @param[in] game The game instance to free.
 */
void free_game(AWO* game);
