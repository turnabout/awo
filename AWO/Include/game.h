#pragma once

#include "types.h"
#include "Game/Stage/stage.h"

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

/*! @brief Creates the game instance.
 *
 *  @note Created with a game state of `Game_Initialized`.
 *
 *  @param[in] window_width The window's initial tiles_width, in pixels.
 *  @param[in] window_height The window's initial tiles_height, in pixels.
 *  @return The created game struct if successful, NULL if an error occurred.
 */
AWO* create_game(int window_width, int window_height);

/*! @brief Prepares game for "design room" (stage editor) mode.
 *
 *  @note Expects game state to be `Game_Initialized`.
 *  @note Sets game state to `Game_Prepared`.
 *
 *  @param[in] game The game.
 *  @param[in] stage The stage to load initially. If NULL, a default stage will be used.
 *  @return TRUE if the game was successfully prepared, FALSE if an error occurred.
 */
Bool prepare_design_room_game(AWO* game, Stage* stage);

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

/*! @brief Direct reference to the game loop.
 *
 * @note Ensure the game's state is `GamePrepared` before running.
 *
 *  @param[in] game The game, typecasted to void*.
 */
void game_loop(void* game);