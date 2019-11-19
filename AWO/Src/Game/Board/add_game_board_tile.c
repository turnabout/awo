#include "Game/Board/_game_board.h"

void add_game_board_tile(
    Game_Board* game_board,
    Game_Clock* game_clock,
    Tiles_Data* tiles_data,
    Tile_Type type,
    Tile_Variation variation,
    Uint8 x,
    Uint8 y
)
{
    // Get tile of given type and variation
    // Tile* tile = get_tile_factory_tile(game_board->tile_factory, type, variation);

    // Add tile to tiles grid
    // game_board->tiles_grid[y][x] = tile;

    // Add the coordinates to the tile's list
    // register_tile_board_position(tile, x, y);
}
