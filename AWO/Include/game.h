#pragma once

/*! @brief Game instance.
 */
typedef struct Game Game;

/*! @brief Game stage struct.
 */
typedef struct Stage Stage;

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
 */
typedef enum Game_Mode {

    // No game mode.
    No_Game_Mode,

    // Stage editor game mode.
    Design_Room_Mode,

    // PVP game mode.
    Gameplay_Mode,

} Game_Mode;

// Min/max amount of players for a game
#define MIN_PLAYER_COUNT 2
#define MAX_PLAYER_COUNT 4

/*! @brief Creates the game instance.
 *
 *  @param[in] window_width The window's initial tiles_width, in pixels.
 *  @param[in] window_height The window's initial tiles_height, in pixels.
 *  @return The created game instance with state of `Game_Initialized`, NULL if an error occurred.
 */
Game* create_game(int window_width, int window_height);

/*! @brief Updates AWO's game window dimensions.
 *
 *  @param[in] game The game object.
 *  @param[in] width The new window width.
 *  @param[in] height The new window height.
 */
void update_game_window_dimensions(Game* game, int width, int height);

/*! @brief Prepare the game for gameplay using the given game mode.
 *
 *  @param[in] game The game object.
 *  @param[in] mode The game mode to prepare the game for.
 *  @param[in] stage Pointer to stage to load. Can be set to NULL with certain game modes.
 *  @param[in] player_COs The players' selected COs.
 *  @return 1 if the game was successfully prepared, 0 if an error occurred.
 */
int prepare_game(
    Game* game,
    Game_Mode mode,
    Stage* stage,
    int player_COs[MAX_PLAYER_COUNT]
);

/*! @brief Undoes the steps done in game preparation.
 *
 * @note Frees memory used by components initialized during game preparation. Should be used after 
 * the game loop is done running.
 *
 *  @param[in] game The game object.
 */
void unprepare_game(Game* game);

/*! @brief Runs the main game loop until `glfwWindowShouldClose` evaluates false.
 *
 *  @param[in] game The game.
 *  @param[in] callback A function called every frame before the game loop. Should return -1 as a 
 *  signal to stop the game from running, or any other value to keep it running.
 *  
 *  @param[in] cb_value Value passed to the callback.
 */
void run_game(Game* game, int (*callback)(void*), void* cb_value);

/*! @brief Gets the game's current state.
 *
 *  @param[in] game The game.
 *  @return The game's currently active state.
 */
Game_State get_game_state(Game* game);

/*! @brief Frees all resources taken up by the game and kills it.
 *
 *  @note Expects game state to be `Game_Initialized`.
 *
 *  @param[in] game The game instance to free.
 */
void free_game(Game* game);
