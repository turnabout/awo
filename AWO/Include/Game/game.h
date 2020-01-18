#pragma once

/*! @brief Game instance.
 */
typedef struct Game Game;

/*! @brief Every possible state for the game.
 */
typedef enum Game_State {

    // The game instance was created, but was not fully initialized, meaning an error happened 
    // during its initialization. Any accumulated error messages should be processed through 
    // `get_next_game_message`, then the game should be freed via `free_game`.
    Game_Unusable,

    // The game instance is initialized, but not prepared for gameplay.
    Game_Initialized,

    // The game is prepared for gameplay.
    Game_Prepared,

    // The game is currently running.
    Game_Running,

} Game_State;

/*! @brief Every possible mode of gameplay the game can use.
 *  Determines which type of game controller the game is currently using.
 *  No_Game_Mode means the game is not in Game_Prepared or Game_Running game state.
 */
typedef enum Game_Mode {

    // No game mode.
    No_Game_Mode,

    // Stage editor game mode.
    Design_Room_Mode,

    // PVP game mode.
    Gameplay_Mode,

} Game_Mode;

/*! @brief Creates the game instance.
 *
 *  @param[in] window_width The window's initial tiles_width, in pixels.
 *  @param[in] window_height The window's initial tiles_height, in pixels.
 *  @return The created game instance with state of `Game_Initialized`, NULL if an error occurred.
 */
Game* create_game(int window_width, int window_height);

/*! @brief Begins running the main game loop.
 *
 *  @note The game must be prepared through one of the "prepare" functions before it can start 
 *  running.
 *
 *  @param[in] game The game.
 *  @param[in] callback Function called every frame before the game loop. Should return -1 as a 
 *  signal to stop the game from running from outside, or any other value to keep it running. Can 
 *  be set to NULL if not needed.
 *  @param[in] cb_value Custom value passed to the callback.
 */
void run_game(Game* game, int (*callback)(void*), void* cb_value);

/*! @brief Gets the game's current mode.
 *
 *  @param[in] game The game.
 *  @return The game's currently active mode.
 */
Game_Mode get_game_mode(Game* game);

/*! @brief Gets the game's current state.
 *
 *  @param[in] game The game.
 *  @return The game's currently active state.
 */
Game_State get_game_state(Game* game);

/*! @brief Updates the dimensions of the game's rendered space (window).
 *
 *  @param[in] game The game object.
 *  @param[in] width The new width.
 *  @param[in] height The new height.
 */
void update_game_dimensions(Game* game, int width, int height);

/*! @brief Frees all resources taken up by the game and kills it.
 *
 *  @note Expects game state to be `Game_Initialized`.
 *
 *  @param[in] game The game instance to free.
 */
void free_game(Game* game);