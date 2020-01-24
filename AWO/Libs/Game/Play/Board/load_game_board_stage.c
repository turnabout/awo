#include <stdlib.h>

#include "Game/Board/_game_board.h"

void allocate_tiles_grid(Game_Board* game_board, Uint8 width, Uint8 height)
{
    game_board->tiles_grid = malloc(sizeof(Tile_Row) * height);

    for (int i = 0; i < height; i++) {
        game_board->tiles_grid[i] = malloc(sizeof(Tile*) * width);
    }
}

void allocate_units_grid(Game_Board* game_board, Uint8 width, Uint8 height)
{
    game_board->units_grid = malloc(sizeof(Unit_Row) * height);

    for (int i = 0; i < height; i++) {
        game_board->units_grid[i] = malloc(sizeof(Unit*) * width);
    }

    // Initialize all unit spots to NULL
    for (Uint8 y = 0; y < height; y++) {
        for (Uint8 x = 0; x < width; x++) {
            game_board->units_grid[y][x] = NULL;
        }
    }
}

void load_game_board_stage(
    Game_Board* game_board, 
    Game_Clock* game_clock,
    Tiles_Data* tiles_data,
    Stage* stage
)
{
    // Allocate space for the grids
    allocate_tiles_grid(game_board, stage->width, stage->height);
    allocate_units_grid(game_board, stage->width, stage->height);

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

    // Add the units from the stage descriptor
    // TODO

    game_board->stage = stage;
}
