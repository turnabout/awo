#include <stdlib.h>

#include "Game/Board/_game_board.h"

void load_game_board_stage(
    Game_Board* game_board, 
    Game_Clock* game_clock,
    Tiles_Data* tiles_data,
    Stage* stage
)
{
    // Allocate space for tiles
    game_board->tiles_grid = malloc(sizeof(Tile_Row) * stage->height);

    for (int i = 0; i < stage->height; i++) {
        game_board->tiles_grid[i] = malloc(sizeof(Tile*) * stage->width);
    }

    // Add the tiles from the stage descriptor
    for (Uint8 y = 0; y < stage->height; y++) {
        for (Uint8 x = 0; x < stage->width; x++) {
            add_game_board_tile(
                game_board, 
                game_clock,
                stage->tiles_grid[y][x].type,
                stage->tiles_grid[y][x].variation,
                x, 
                y
            );
        }
    }

    // Allocate space for units
    game_board->units_grid = malloc(sizeof(Unit_Row) * stage->height);

    for (int i = 0; i < stage->height; i++) {
        game_board->units_grid[i] = malloc(sizeof(Unit*) * stage->width);
    }

    // Add the units from the stage descriptor
    // TODO

    game_board->stage = stage;
}
