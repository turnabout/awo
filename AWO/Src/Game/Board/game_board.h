#pragma once

#include "types.h"
#include "Game/Clock/game_clock.h"
#include "Game/Data/Tile/tiles_data.h"
#include "Game/Renderer/game_renderer.h"
#include "Game/Stage/stage_descriptor.h"

/*! @brief Represents the game board used by players during gameplay. Contains all game entities.
 */
typedef struct Game_Board Game_Board;

/*! @brief Creates the game board.
 *
 *  @param[in] tiles_data The tiles data object.
 *  @param[in] game_clock The game clock object.
 *  @return The created game board object.
 */
Game_Board* create_game_board(Tiles_Data* tiles_data, Game_Clock* game_clock);

/*! @brief Updates the game board and its entities.
 *
 *  @param[in] game_board The game board.
 */
void update_game_board(Game_Board* game_board);

/*! @brief Loads stage described by the given stage descriptor into the game board.
 *
 *  @param[in] game_board The game board.
 *  @param[in] stage_descriptor Descriptor detailing the stage to load.
 */
void load_game_board_stage(Game_Board* game_board, Stage_Descriptor* stage_descriptor);

/*! @brief Frees all memory occupied by the game board and its contents.
 *
 *  @param[in] game_board The game board.
 */
void free_game_board(Game_Board* game_board);

