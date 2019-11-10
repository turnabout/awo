#pragma once

typedef struct Game Game;

/*! @brief Initializes game.
 *
 *  @param[in] game_board_width The game board's width, in tiles.
 *  @param[in] game_board_height The game board's height, in tiles.
 *  @param[in] window_width The window's initial width, in pixels.
 *  @param[in] window_height The window's initial height, in pixels.
 *  @return The game struct if successful, NULL if an error occurred.
 */
Game* init_game(int game_board_width, int game_board_height, int window_width, int window_height);

/*! @brief Starts running the game.
 *
 *  @param[in] game The game struct.
 */
void run_game(Game* game);

/*! @brief Frees used up resources and exits the game.
 *
 *  @param[in] game The game struct.
 */
void exit_game(Game* game);