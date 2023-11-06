#include "Game/Board/_game_board.h"
#include "Game/Entity/Tile/tile.h"

void add_game_board_tile(
    Game_Board* game_board,
    Clock* game_clock,
    Tile_Type tile_type,
    int tile_variation,
    Uint8 x,
    Uint8 y
)
{
    Tile* tile;

    if (tile_type >= NEUTRAL_TILE_TYPE_FIRST && tile_type <= NEUTRAL_TILE_TYPE_LAST) {
        tile = game_board->tiles_grid[y][x] = (Tile*)create_neutral_tile(
            game_clock,
            game_board->tiles_data,
            tile_type,
            tile_variation,
            x,
            y
        );
    } else if (tile_type >= PROPERTY_TILE_TYPE_FIRST && tile_type <= PROPERTY_TILE_TYPE_LAST) {

        // The player who owns this property
        Player_Index player_index = (Player_Index)tile_variation;

        // Create the property tile & register it with the game board's grid
        tile = game_board->tiles_grid[y][x] = (Tile*)create_property_tile(
            game_clock,
            game_board->tiles_data,
            tile_type,
            game_board->players[player_index],
            x,
            y
        );

        // Register the property with the player who owns it
        register_game_board_player_property(game_board, (Property_Tile*)tile);
    } else {
        // TODO: log error
        return;
    }

    // Make initial call to the tile's render grid & palette update functions
    tile->update_grid(game_board->game_renderer, (void*)tile, 0);
    tile->update_palette(game_board->game_renderer, (void*)tile, 0);
}
