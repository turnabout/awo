#pragma once

#include "definitions.h"

/*! @brief Prepares game for "design room" (stage editor) mode.
 *
 *  @note Expects game state to be `Game_Initialized`.
 *  @note Sets game state to `Game_Prepared`.
 *
 *  @param[in] game The game.
 *  @return TRUE if the game was successfully prepared, FALSE if an error occurred.
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

/*! @brief Frees all resources taken up by the game and kills it.
 *
 *  @note Expects game state to be `Game_Initialized`.
 *
 *  @param[in] game The game instance to free.
 */
void free_game(AWO* game);
