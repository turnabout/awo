#include <stdlib.h>

#include "Game/Board/_game_board.h"
#include "Game/Data/Palette/game_palette.h"
#include "Game/Player/player.h"

Game_Board* create_game_board(
    Game_Clock* game_clock, 
    Tiles_Data* tiles_data, 
    Stage_Descriptor* stage,
    CO_Type player_COs[MAX_PLAYER_COUNT]
)
{
    Game_Board* game_board = malloc(sizeof(Game_Board));

    // Set players list
    game_board->players_list = create_players_list(
        stage->player_count, 
        stage->player_armies, 
        player_COs
    );

    // Create the players' properties lists
    for (int i = 0; i < game_board->players_list->player_count; i++) {
        game_board->player_properties[i] = create_linked_list(NULL, 0);
    }

    load_game_board_stage(game_board, game_clock, tiles_data, stage);

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
