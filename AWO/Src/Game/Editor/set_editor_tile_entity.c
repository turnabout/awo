#include "Game/Editor/_game_editor.h"

void set_editor_tile_entity(
    Game_Editor* editor,
    Game_Board* game_board,
    Game_Clock* game_clock
)
{
    int applied_variation = editor->selected_entity_var;

    // If no variation selected
    if (applied_variation == SELECTED_ENTITY_VAR_NONE) {

        // Property tiles: no variation is invalid
        if (
            editor->selected_entity_type >= PROPERTY_TILE_TYPE_FIRST &&
            editor->selected_entity_type >= PROPERTY_TILE_TYPE_LAST
        ) {
            return;
        }

        // Neutral tiles: use auto-vars to determine the variation to use
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