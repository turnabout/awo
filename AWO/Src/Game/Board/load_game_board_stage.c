#include "Game/Board/_game_board.h"

void load_game_board_stage(Game_Board* game_board, Stage_Descriptor* stage_descriptor)
{
    // Allocate space for tiles
    game_board->tiles_grid = (Tile_Row*)malloc(sizeof(Tile_Row) * stage_descriptor->height);

    for (int i = 0; i < stage_descriptor->height; i++) {
        game_board->tiles_grid[i] = (Tile**)malloc(sizeof(Tile*) * stage_descriptor->width);
    }

    // Add the tiles from the stage descriptor
    for (int y = 0; y < stage_descriptor->height; y++) {
        for (int x = 0; x < stage_descriptor->width; x++) {

            Tile_Descriptor* tile = (
                (stage_descriptor->tile_descriptors + x) +
                (stage_descriptor->width * y)
            );

            add_game_board_tile(game_board, tile->type, tile->variation, x, y);
        }
    }

    game_board->stage = stage_descriptor;
}
