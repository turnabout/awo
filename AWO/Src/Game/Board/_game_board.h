#pragma once

#include "Game/Board/game_board.h"

typedef Tile** Tile_Row;

struct Game_Board {
    // Contains all tiles on the game board. tiles[board_y][board_x]
    Tile_Row* tiles_grid;

    // Descriptor of the loaded stage.
    Stage_Descriptor* stage;

    // Reference to the game clock module.
    // Game_Clock* game_clock;

    // Indices of the currently active tile and fog tile palettes.
    // GLfloat active_tile_palette_index, active_fog_tile_palette_index;
};

/*! @brief Loads stage described by the given stage descriptor into the game board.
 *
 *  @param[in] game_board The game board.
 *  @param[in] game_clock The game clock object.
 *  @param[in] tiles_data The tiles data object.
 *  @param[in] stage_descriptor Descriptor detailing the stage to load.
 */
void load_game_board_stage(
    Game_Board* game_board, 
    Game_Clock* game_clock,
    Tiles_Data* tiles_data,
    Stage_Descriptor* stage_descriptor
);

/*! @brief Adds a new tile of the given type and variation to the game board at x/y coordinate.
 *
 *  @param[in] game_board The game board.
 *  @param[in] game_clock The game clock.
 *  @param[in] tiles_data The tiles data object.
 *  @param[in] type Type of the newly added tile.
 *  @param[in] variation Variation of the newly added tile.
 *  @param[in] x Game board x coordinate of the new tile.
 *  @param[in] y Game board y coordinate of the new tile.
 */
void add_game_board_tile(
    Game_Board* game_board,
    Game_Clock* game_clock,
    Tiles_Data* tiles_data,
    Tile_Type type,
    Tile_Variation variation,
    Uint8 x,
    Uint8 y
);
