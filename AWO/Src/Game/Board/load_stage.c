#include <stdlib.h>

#include "Game/Board/_game_board.h"

#define STAGE_STRING_SEPARATOR_CHARACTER 255

Bool load_stage(Game_Board* game_board, char* stage_str)
{
    printf("%s\n", stage_str);

    add_game_board_tile(game_board, Sea, Middle, 0, 0);
    add_game_board_tile(game_board, Sea, Middle, 1, 0);
    add_game_board_tile(game_board, Sea, Middle, 2, 0);
    add_game_board_tile(game_board, Sea, Middle, 3, 0);
    add_game_board_tile(game_board, Sea, Middle, 4, 0);

    add_game_board_tile(game_board, Sea, Bottom, 0, 1);
    add_game_board_tile(game_board, Sea, Bottom, 1, 1);
    add_game_board_tile(game_board, Sea, Bottom, 2, 1);
    add_game_board_tile(game_board, Sea, Bottom, 3, 1);
    add_game_board_tile(game_board, Sea, Bottom, 4, 1);

    add_game_board_tile(game_board, Plain, Default, 0, 2);
    add_game_board_tile(game_board, Plain, Default, 1, 2);
    add_game_board_tile(game_board, Plain, Default, 2, 2);
    add_game_board_tile(game_board, Plain, Default, 3, 2);
    add_game_board_tile(game_board, Plain, Default, 4, 2);

    free(stage_str);

    return TRUE;
}
