#include <stdlib.h>

#include "Game/Board/_game_board.h"
#include "Game/Data/Palette/game_palette.h"
#include "Game/Player/player.h"

Game_Board* create_game_board(
    Game_Clock* game_clock, 
    Tiles_Data* tiles_data, 
    Stage_Descriptor* stage_descriptor,
    Players_List* players_list
)
{
    Game_Board* game_board = malloc(sizeof(Game_Board));

    game_board->players_list = players_list;
    load_game_board_stage(game_board, game_clock, tiles_data, stage_descriptor);

    // game_board->active_tile_palette_index = get_active_tile_palette_index(0);
    // game_board->active_fog_tile_palette_index = get_active_tile_palette_index(1);

    return game_board;
}

void update_game_board(Game_Board* game_board)
{
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
