#include "Game/Editor/_game_editor.h"

void set_editor_property_entity(Game_Editor* editor, Game_Board* board, Game_Clock* clock)
{
    // No variation selected is invalid for properties
    if (editor->selected_entity_var == SELECTED_ENTITY_VAR_NONE) {
        return;
    }

    // Update the game board tile at the given coordinates
    edit_game_board_tile(
        board,
        clock,
        editor->selected_entity_type,
        editor->selected_entity_var,
        editor->entity_x,
        editor->entity_y
    );

    // Apply auto-vars to surrounding tiles
    // TODO
}