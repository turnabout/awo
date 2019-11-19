#pragma once

#include "Game/Board/game_board.h"
#include "Game/Entity/Tile/tile.h"

typedef Tile** Tile_Row;

struct Game_Board {
    // Contains all tiles on the game board. tiles[board_y][board_x]
    Tile_Row* tiles_grid;

    // Descriptor of the loaded stage.
    Stage_Descriptor* stage;

    // Reference to the game clock module.
    Game_Clock* game_clock;

    // Indices of the currently active tile and fog tile palettes.
    GLfloat active_tile_palette_index, active_fog_tile_palette_index;
};

/*! @brief Adds a new tile of the given type and variation to the game board at x/y coordinate.
 *
 *  @param[in] game_board The game board.
 *  @param[in] type Type of the newly added tile.
 *  @param[in] variation Variation of the newly added tile.
 *  @param[in] x Game board x coordinate of the new tile.
 *  @param[in] y Game board y coordinate of the new tile.
 */
void add_game_board_tile(
    Game_Board* game_board,
    Tile_Type type,
    Tile_Variation variation,
    Uint8 x,
    Uint8 y
);
