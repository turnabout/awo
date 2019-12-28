#include "Game/Editor/_game_editor.h"

void set_editor_tile_entity(Game_Editor* editor, Game_Board* board, Game_Clock* clock)
{
    edit_game_board_tile(
        board,
        clock,
        editor->selected_entity_type,
        editor->selected_entity_var,
        editor->entity_x,
        editor->entity_y
    );


    // If a specific variation was selected, no need to apply auto-vars
    if (editor->selected_entity_var != SELECTED_ENTITY_VAR_NONE) {

        return;
    }

    // No specific variation selected, apply auto-vars to new tile & its surrounding tiles
    apply_autovar(editor, board, clock, editor->entity_x, editor->entity_y);

    // TODO: apply to surrounding tiles
}