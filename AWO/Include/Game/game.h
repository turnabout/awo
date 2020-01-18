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