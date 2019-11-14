#pragma once

#include "Game/Clock/game_clock.h"
#include "Game/Data/Tile/tiles_data.h"
#include "Game/Renderer/game_renderer.h"
#include "Game/Clock/Clock_Subscriber/clock_subscriber.h"

/*! @brief Represents the game board used by players during gameplay. Contains all game entities.
 */
typedef struct Game_Board Game_Board;

/*! @brief Creates the game board.
 *
 *  @param[in] tiles_data The tiles data object.
 *  @param[in] game_clock The game clock object.
 *  @param[in] tiles_width The tiles_width of the game board in tiles.
 *  @param[in] tiles_height The tiles_height of the game board in tiles.
 *  @param[in] tiles_clock_sub The tiles clock subscription module.
 *  @return The created game board object.
 */
Game_Board* create_game_board(
    Tiles_Data* tiles_data,
    Game_Clock* game_clock,
    int width,
    int height,
    Clock_Subscriber* tiles_clock_sub
);

/*! @brief Updates the game board and its entities.
 *
 *  @param[in] game_board The game board.
 */
void update_game_board(Game_Board* game_board);

/*! @brief Loads stage into the game board.
 *
 *  @param[in] game_board The game board.
 *  @param[in] stage_str String representing the stage to load, to be processed by the function.
 *  @return Whether the stage string was valid and loaded successfully.
 */
Bool load_stage(Game_Board* game_board, char* stage_str);

/*! @brief Frees all memory occupied by the game board and its contents.
 *
 *  @param[in] game_board The game board.
 */
void free_game_board(Game_Board* game_board);

