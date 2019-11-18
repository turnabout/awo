#include <stdlib.h>

#include "conf.h"
#include "Game/Board/_game_board.h"
#include "Game/Data/Palette/game_palette.h"

Game_Board* create_game_board(
    Tiles_Data* tiles_data, 
    Game_Clock* game_clock
)
{
    Game_Board* game_board = malloc(sizeof(Game_Board));

    // game_board->tile_factory = create_tile_factory(tiles_data, game_clock, tiles_clock_sub);
    // game_board->active_tile_palette_index = get_active_tile_palette_index(0);
    // game_board->active_fog_tile_palette_index = get_active_tile_palette_index(1);
    game_board->game_clock = game_clock;

    return game_board;
}

void update_game_board(Game_Board* game_board)
{
}

void add_game_board_tile(
    Game_Board* game_board, 
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

void fill_game_board_tiles(Game_Board* game_board, Tile_Type type, Tile_Variation variation)
{
    for (int y = 0; y < game_board->stage->height; y++) {
        for (int x = 0; x < game_board->stage->width; x++) {
            add_game_board_tile(game_board, type, variation, x, y);
        }
    }
}

void free_game_board(Game_Board* game_board)
{
    if (game_board != NULL) {
        for (int i = 0; i < game_board->stage->height; i++) {
            free(game_board->tiles_grid[i]);
        }

        free(game_board->tiles_grid);
        free(game_board);
    }
}
