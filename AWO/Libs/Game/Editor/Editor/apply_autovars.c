#include "_game_editor.h"

void apply_autovar(Game_Editor* editor, Game_Board* board, Clock* clock, Uint8 x, Uint8 y)
{

    Tile_Type middle_tile_type = get_game_board_tile_type(board, x, y);

    // Don't apply if middle tile is a property OR is out of bounds
    if (
        middle_tile_type >= PROPERTY_TILE_TYPE_FIRST || 
        middle_tile_type >= PROPERTY_TILE_TYPE_LAST ||
        middle_tile_type == OOB
    ) {
        return;
    }

    Tile_Variation new_var = get_tile_auto_var(
        editor->tiles_data,
        middle_tile_type,
        get_game_board_tile_type(board, x, y - 1),
        get_game_board_tile_type(board, x + 1, y),
        get_game_board_tile_type(board, x, y + 1),
        get_game_board_tile_type(board, x - 1, y)
    );

    printf(
        "Applying auto-var to %s (%d, %d): %s\n", 
        tile_type_str[middle_tile_type],
        x,
        y,
        tile_var_str[new_var]
    );

    edit_game_board_tile(board, clock, middle_tile_type, new_var, x, y);
}
