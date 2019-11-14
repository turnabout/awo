#include "Game/Board/_game_board.h"

void load_game_board_stage(Game_Board* game_board, Stage_Descriptor* stage_descriptor)
{
    for (int y = 0; y < stage_descriptor->height; y++) {
        for (int x = 0; x < stage_descriptor->width; x++) {

            Tile_Descriptor* tile = (
                (stage_descriptor->tile_descriptors + x) +
                (stage_descriptor->width * y)
            );

            add_game_board_tile(game_board, tile->type, tile->variation, x, y);
        }
    }

    game_board->loaded_stage = stage_descriptor;
}
