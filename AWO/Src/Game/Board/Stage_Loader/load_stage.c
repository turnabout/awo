#include <stdlib.h>

#include "Utilities/utilities.h"
#include "Game/Board/_game_board.h"
#include "Game/Board/Stage_Loader/_stage_loader.h"

Bool load_stage(Game_Board* game_board, char* stage_str, Tiles_Data* tiles_data)
{
    // Translate the hex string into a useable data bytes array
    Uint8* stage_data;
    size_t data_length;
 
    if ((stage_data = hex_string_to_data(stage_str, &data_length)) == NULL || 
         !validate_stage_data(stage_data, data_length, tiles_data)
    ) {
        free(stage_str);
        return FALSE;
    }

    // Process data byte array
    for (size_t i = 0; i < data_length; i++) {
    }

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
    free(stage_data);

    return TRUE;
}
