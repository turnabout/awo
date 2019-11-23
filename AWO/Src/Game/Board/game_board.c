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

    // Set players
    game_board->player_count = stage->player_count;

    for (int i = 0; i < MAX_PLAYER_COUNT; i++) {
        game_board->players[i] = create_player(
            i,
            stage->player_armies[i],
            player_COs[i]
        );

        game_board->player_properties[i] = create_linked_list(NULL, 0);
    }

    // Set neutral player, for holding neutral properties
    game_board->players[MAX_PLAYER_COUNT] = create_player(
        Player_Index_Neutral,
        ARMY_TYPE_NEUTRAL,
        Andy
    );
    game_board->player_properties[MAX_PLAYER_COUNT] = create_linked_list(NULL, 0);

    // Load the given stage
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
