#pragma once

#include "../Game_Window/game_window.h"

/*! @brief Game instance.
 */
typedef struct Game Game;

/*! @brief Begins running the main game loop using the given game instance.
 *
 *  @param[in] game The game.
 *  @param[in] game_window The game window instance.
 *  @param[in] callback Function called every frame before the game loop. Should return -1 as a 
 *  signal to stop the game from running from outside, or any other value to keep it running. Can 
 *  be set to NULL if not needed.
 *  @param[in] cb_value Custom value passed to the callback.
 */
void run_game(
    Game* game,
    Game_Window* game_window,
    int (*callback)(void*),
    void* cb_value
);

/*! @brief Manually tell the game that the game window's dimensions were updated.
 *
 *  @note This should only be called along with update_game_window_dimensions when the game window 
 *  dimensions were updated after the game was created, but before the game has started running.
 *
 *  @param[in] game The game.
 *  @param[in] new_width The new width. Same that was passed to update_game_window_dimensions.
 *  @param[in] new_height The new height. Same that was passed to update_game_window_dimensions.
 */
void update_game_dimensions(Game* game, int new_width, int new_height);
