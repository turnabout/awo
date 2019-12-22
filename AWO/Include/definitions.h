#pragma once

/*! @brief Different states the game can be in.
 */
typedef enum Game_State {

    // The game has been created and is initialized. Game data is accessible.
    Game_Initialized,

    // The game has been prepared for gameplay, but is not yet running.
    Game_Prepared,

    // The game's loop is running.
    Game_Running,

} AWO_State;

/*! @brief Game instance.
 * 
 *  @note Use `get_game_state` to get the current state of the game.
 *  Certain functions can only be called while the game is in certain states.
 */
typedef struct Game AWO;