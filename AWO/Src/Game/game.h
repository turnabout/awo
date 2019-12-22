#pragma once

typedef struct Game Game;

/*! @brief Initializes game.
 *
 *  @param[in] window_width The window's initial tiles_width, in pixels.
 *  @param[in] window_height The window's initial tiles_height, in pixels.
 *  @return The game struct if successful, NULL if an error occurred.
 */
Game* create_game(int window_width, int window_height);

/*! @brief Starts running the main game loop.
 *
 *  @param[in] game The game struct.
 */
void run_game(Game* game);

/*! @brief The game loop.
 *
 *  @param[in] game The game struct.
 */
void game_loop(void* game);

/*! @brief Frees used up resources and exits the game.
 *
 *  @param[in] game The game struct.
 */
void exit_game(Game* game);