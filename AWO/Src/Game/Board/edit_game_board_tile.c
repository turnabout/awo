#include "Game/Board/_game_board.h"
#include "Game/Entity/Tile/tile.h"

void edit_game_board_tile(
    Game_Board* game_board,
    Game_Clock* game_clock,
    Tiles_Data* tiles_data,
    Tile_Type new_type,
    int new_variation,
    Uint8 x,
    Uint8 y
)
{
    Tile* old_tile = game_board->tiles_grid[y][x];

    // Same tile type, only need to edit the tile's variation
    if (old_tile->type == new_type) {

        // TODO
        return;
    }

    // New tile type, delete the old tile and replace with a new one
    old_tile->delete(old_tile, game_clock, tiles_data);

    add_game_board_tile(
        game_board,
        game_clock,
        tiles_data,
        new_type,
        new_variation,
        x,
        y
    );
}
