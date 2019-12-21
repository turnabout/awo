#include "Game/Editor/_game_editor.h"

void set_neutral_tile_entity(
    Game_Editor* editor,
    Game_Board* game_board,
    Game_Clock* game_clock
)
{
    // If no variation, invalid if property
    int applied_variation = editor->selected_entity_var;

    // If no variation selected, use auto-vars to determine the variation to use
    if (applied_variation == TILE_VAR_NONE) {
        // TODO
        return;
    }

    // Update the game board tile at the given coordinates
    edit_game_board_tile(
        game_board,
        game_clock,
        editor->selected_entity_type,
        applied_variation,
        editor->entity_x,
        editor->entity_y
    );

    // Apply autovar to surrounding tiles
    // TODO
}
