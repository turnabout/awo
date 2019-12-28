#include "Game/Editor/_game_editor.h"

void apply_autovar(Game_Editor* editor, Game_Board* board, Game_Clock* clock, Uint8 x, Uint8 y)
{

    Tile_Type middle_tile_type = get_game_board_tile_type(board, x, y);

    // Don't apply if middle tile is out of bounds
    if (middle_tile_type == OOB) {
        return;
    }

    edit_game_board_tile(
        board,
        clock,
        middle_tile_type,

        get_tile_auto_var(
            editor->tiles_data,
            middle_tile_type,
            get_game_board_tile_type(board, x,     y - 1),
            get_game_board_tile_type(board, x + 1, y),
            get_game_board_tile_type(board, x,     y + 1),
            get_game_board_tile_type(board, x - 1, y)
        ),

        x,
        y
    );
}
