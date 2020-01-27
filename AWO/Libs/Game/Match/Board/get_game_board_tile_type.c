#include "Game/Board/_game_board.h"

Tile_Type get_game_board_tile_type(Game_Board* game_board, int x, int y)
{
    // No tile at coordinates (out of bounds)
    if (x < 0 || x >= game_board->stage->width || y < 0 || y >= game_board->stage->height) {
        return OOB;
    }

    return game_board->tiles_grid[y][x]->type;
}
