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

/*! @brief Fills the game board with tile of the given type & variation.
 *
 *  @param[in] game_board The game board.
 *  @param[in] type Type of the tile to fill with.
 *  @param[in] variation Variation of the tile to fill with.
 */
void fill_game_board_tiles(Game_Board* game_board, Tile_Type type, Tile_Variation variation);

/*! @brief Edits the tile type/variation at given board x and y indices.
 *
 *  @param[in] game_board The game board.
 *  @param[in] board_x The board x index of the tile to edit.
 *  @param[in] board_y The board y index of the tile to edit.
 *  @param[in] type Type given to the tile.
 *  @param[in] variation Variation given to the tile.
 */
/*
void edit_game_board_tile(
    Game_Board* game_board,
    int board_x,
    int board_y,
    Tile_Type type,
    Tile_Variation variation
);
*/

/*! @brief Returns the tile type of the tile at given board indices.
 *
 *  @param[in] game_board The game board.
 *  @param[in] board_x The board x index of the tile.
 *  @param[in] board_y The board y index of the tile.
 *  @return The tile type of the board found at the given x/y indices.
 */
// Tile_Type get_game_board_tile_type(Game_Board* game_board, int board_x, int board_y);

/*! @brief Gets the board indices of the tile found at given screen coordinates.
 *
 *  @param[in] screen_x The screen x coordinate.
 *  @param[in] screen_y The screen y coordinate.
 *  @param[out] board_x The board x index of the found tile.
 *  @param[out] board_y The board y index of the found tile.
 */
/*
void get_game_board_screen_coordinate_indices(
    int screen_x, 
    int screen_y, 
    int* board_x, 
    int* board_y
);
*/

/*! @brief Frees all memory occupied by the game board and its contents.
 *
 *  @param[in] game_board The game board.
 */
void free_game_board(Game_Board* game_board);

