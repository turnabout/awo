#pragma once

#include "Game/Clock/game_clock.h"
#include "Game/Data/Tile/tiles_data.h"
#include "Game/Sprite_Batch/sprite_batch.h"

/*! @brief Represents the game board used by players during gameplay. Contains all game entities.
 */
typedef struct Game_Board Game_Board;

/*! @brief Creates the game board. Width/height determine the game board's dimensions in tiles.
 */
Game_Board* GB_create(Tiles_Data* tiles_data, Game_Clock* game_clock, int width, int height);

/*! @brief Updates the game board and its entities.
 *
 *  @param[in] game_board The game board.
 */
void GB_update(Game_Board* game_board);

/*! @brief Draws the game board entities.
 *
 *  @param[in] game_board The game board.
 *  @param[in] sprite_batch The sprite batch object used to draw game sprites.
 */
void GB_draw(Game_Board* game_board, Sprite_Batch* sprite_batch);

/*! @brief Fills the game board with tile of the given type & variation.
 *
 *  @param[in] game_board The game board.
 *  @param[in] type Type of the tile to fill with.
 *  @param[in] variation Variation of the tile to fill with.
 */
void GB_fill_tiles(Game_Board* game_board, Tile_Type type, Tile_Variation variation);

/*! @brief Edits the tile type/variation at given board x and y indices.
 *
 *  @param[in] game_board The game board.
 *  @param[in] board_x The board x index of the tile to edit.
 *  @param[in] board_y The board y index of the tile to edit.
 *  @param[in] type Type given to the tile.
 *  @param[in] variation Variation given to the tile.
 */
void GB_edit_tile(
    Game_Board* game_board,
    int board_x,
    int board_y,
    Tile_Type type,
    Tile_Variation variation
);

/*! @brief Gets the board indices of the tile found at given screen coordinates.
 *
 *  @param[in] game_board The game board.
 *  @param[in] screen_x The screen x coordinate.
 *  @param[in] screen_y The screen y coordinate.
 *  @param[out] board_x The board x index of the found tile.
 *  @param[out] board_y The board y index of the found tile.
 */
void GB_get_pointer_board_coords(
    Game_Board* game_board, 
    int screen_x, 
    int screen_y, 
    int* board_x, 
    int* board_y
);

/*! @brief Returns the tile type of the tile at given board indices.
 *
 *  @param[in] game_board The game board.
 *  @param[in] board_x The board x index of the tile.
 *  @param[in] board_y The board y index of the tile.
 *  @return The tile type of the board found at the given x/y indices.
 */
Tile_Type GB_get_tile_type_at_coords(Game_Board* game_board, int board_x, int board_y);

/*! @brief Frees all memory occupied by the game board and its contents.
 *
 *  @param[in] game_board The game board.
 */
void GB_free(Game_Board* game_board);

// Adds a unit to the game board
// void GB_add_unit(Game_Board* gb, Unit* u);
