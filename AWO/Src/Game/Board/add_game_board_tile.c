#include "Game/Board/_game_board.h"
#include "Game/Entity/Tile/tile.h"

void add_game_board_tile(
    Game_Board* game_board,
    Game_Clock* game_clock,
    Tiles_Data* tiles_data,
    Tile_Type tile_type,
    int tile_variation,
    Uint8 x,
    Uint8 y
)
{
    if (tile_type >= NEUTRAL_TILE_TYPE_FIRST && tile_type <= NEUTRAL_TILE_TYPE_LAST) {
        game_board->tiles_grid[y][x] = (Tile*)create_neutral_tile(
            game_clock,
            tiles_data,
            tile_type,
            tile_variation,
            x,
            y
        );
        
    } else if (tile_type >= PROPERTY_TILE_TYPE_FIRST && tile_type <= PROPERTY_TILE_TYPE_LAST) {
        game_board->tiles_grid[y][x] = (Tile*)create_property_tile(
            game_clock,
            tiles_data,
            tile_type,
            tile_variation,
            x,
            y
        );
    }
}
