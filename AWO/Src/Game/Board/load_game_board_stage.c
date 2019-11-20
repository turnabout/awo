#include <stdlib.h>

#include "Game/Board/_game_board.h"

void load_game_board_stage(
    Game_Board* game_board, 
    Game_Clock* game_clock,
    Tiles_Data* tiles_data,
    Stage_Descriptor* stage_descriptor
)
{
    // Allocate space for tiles
    game_board->tiles_grid = (Tile_Row*)malloc(sizeof(Tile_Row) * stage_descriptor->height);

    for (int i = 0; i < stage_descriptor->height; i++) {
        game_board->tiles_grid[i] = (Tile**)malloc(sizeof(Tile*) * stage_descriptor->width);
    }

    // Add the tiles from the stage descriptor
    for (Uint8 y = 0; y < stage_descriptor->height; y++) {
        for (Uint8 x = 0; x < stage_descriptor->width; x++) {

            Tile_Descriptor* tile_descriptor = (
                (stage_descriptor->tile_descriptors + x) +
                (stage_descriptor->width * y)
            );

            add_game_board_tile(
                game_board, 
                game_clock,
                tiles_data,
                tile_descriptor->type, 
                tile_descriptor->variation, 
                x, 
                y
            );
        }
    }

    game_board->stage = stage_descriptor;
}
