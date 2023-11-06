#include "./_game_editor.h"

void set_editor_tile_entity(Game_Editor* editor, Game_Board* board, Clock* clock)
{
    // If a specific variation was selected, no need to apply auto-vars
    if (editor->selected_entity_var != SELECTED_ENTITY_VAR_NONE) {

        edit_game_board_tile(
            board,
            clock,
            editor->selected_entity_type,
            editor->selected_entity_var,
            editor->entity_x,
            editor->entity_y
        );

        return;
    }

    // No specific variation selected, first apply the type & its default variation
    edit_game_board_tile(
        board,
        clock,
        editor->selected_entity_type,
        get_default_tile_variation(editor->tiles_data, editor->selected_entity_type),
        editor->entity_x,
        editor->entity_y
    );

    // Apply auto-vars to new tile & its surrounding tiles
    apply_autovar(editor, board, clock, editor->entity_x, editor->entity_y);

    apply_autovar(editor, board, clock, editor->entity_x - 1, editor->entity_y);
    apply_autovar(editor, board, clock, editor->entity_x + 1, editor->entity_y);
    apply_autovar(editor, board, clock, editor->entity_x,     editor->entity_y - 1);
    apply_autovar(editor, board, clock, editor->entity_x,     editor->entity_y + 1);
}