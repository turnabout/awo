#include <stdlib.h>

#include "Utilities/Message_Service/message_service.h"
#include "Game/Editor/_game_editor.h"

Game_Editor* create_game_editor(
    Tiles_Data* tiles_data,
    Units_Data* units_data,
    int* window_width, 
    int* window_height
)
{
    Game_Editor* editor = malloc(sizeof(Game_Editor));

    editor->mode = Editor_Mode_Neutral;

    editor->selected_entity_update_cb = NULL;
    editor->selected_entity_type = SELECTED_ENTITY_TYPE_NONE;
    editor->selected_entity_var = SELECTED_ENTITY_VAR_NONE;

    editor->entity_x = ENTITY_COORDINATE_NONE;
    editor->entity_y = ENTITY_COORDINATE_NONE;

    editor->tiles_data = tiles_data;
    editor->units_data = units_data;

    editor->hovered_x = editor->hovered_y = -1;

    editor->entity_placeable = TRUE;

    // Start with default editing values
    // TODO: remove, should be set from outside
    update_editor_selected_entity(editor, Editor_Entity_Type_Tile, Shore, SELECTED_ENTITY_VAR_NONE);

    // editor->selected_entity = SE_create(window_width, window_height);

    return editor;
}

void update_editor_selected_entity(
    Game_Editor* editor, 
    Game_Editor_Entity_Kind kind, 
    int type, 
    int variation
)
{
    // Set the kind of entity that should now be selected
    if (kind == Editor_Entity_Type_Tile) {

        // Validate tile type & set appropriate callback
        if (is_tile_type_neutral(type)) {

            editor->selected_entity_update_cb = set_editor_tile_entity;
            editor->selected_entity_var = SELECTED_ENTITY_VAR_NONE;
            editor->placement_rules = get_tile_placement_rules(editor->tiles_data, type);

        } else if (is_tile_type_property(type)) {

            // TODO: validate the given variation (player index) is valid

            editor->selected_entity_update_cb = set_editor_property_entity;
            editor->selected_entity_var = variation;
        } else {

            // Invalid tile type
            printe("Game editor: invalid tile type given: '%d'", type);
            editor->selected_entity_type = SELECTED_ENTITY_TYPE_NONE;
            editor->selected_entity_var = SELECTED_ENTITY_VAR_NONE;
            return;
        }

        printi("Updating selection to tile: %s", tile_type_str[type]);

    } else if (kind == Editor_Entity_Type_Unit) {
        editor->selected_entity_update_cb = set_editor_unit_entity;
    } else {

        // Invalid entity kind
        printe("Game editor: invalid entity kind given: '%d'", kind);
        editor->selected_entity_type = SELECTED_ENTITY_TYPE_NONE;
        editor->selected_entity_var = SELECTED_ENTITY_VAR_NONE;
        return;
    }

    // Set the selected entity's type
    editor->selected_entity_type = type;
}

void update_game_editor(
    Game_Editor* editor,
    Game_Renderer* game_renderer,
    Game_Board* game_board,
    Game_Clock* game_clock,
    Game_Cursor* cursor,
    Mouse_State* mouse_state
)
{
    // Check if hovered tile changed
    if (editor->hovered_x != cursor->hovered_x || editor->hovered_y != cursor->hovered_y) {

        // Update whether the selected tile is placeable at new hovered coordinates
        editor->entity_placeable = is_editor_tile_placeable(
            editor->placement_rules,
            game_board,
            cursor->hovered_x,
            cursor->hovered_y
        );

        // Update game cursor style based on whether entity is placeable
        update_cursor_style(
            cursor, 
            (editor->entity_placeable) 
                ? Game_Cursor_Regular_Style 
                : Game_Cursor_X_Style
        );

        // Save currently hovered tile
        editor->hovered_x = cursor->hovered_x;
        editor->hovered_y = cursor->hovered_y;
    }

    // Check if we should attempt to edit
    if (mouse_state->buttons[MOUSE_BUTTON_LEFT] == BUTTON_DOWN) {

        // Exit early if entity cannot be placed
        if (
            editor->entity_placeable == FALSE ||
            editor->selected_entity_type == SELECTED_ENTITY_TYPE_NONE || 
            editor->selected_entity_update_cb == NULL
        ) {
            return;
        }

        // If the mouse was already held down on this grid tile, don't bother editing
        if (
            editor->mode == Editor_Mode_Dragging &&
            editor->hovered_x == editor->entity_x && 
            editor->hovered_y == editor->entity_y
        ) {
            return;
        }

        // Edit the entity at these coordinates
        editor->entity_x = editor->hovered_x;
        editor->entity_y = editor->hovered_y;

        editor->selected_entity_update_cb(editor, game_board, game_clock);
        editor->mode = Editor_Mode_Dragging;

    } else if (editor->mode == Editor_Mode_Dragging) {

        // No longer dragging, reset editor mode
        editor->mode = Editor_Mode_Neutral;

    } else if (
        mouse_state->buttons[MOUSE_BUTTON_LEFT] == BUTTON_DOWN_START && 
        get_key_state(KEY_LEFT_ALT) == BUTTON_DOWN
    ) {

        // Alt + click on tile, attempt to update selected tile to hovered one
        if (editor->hovered_x != -1 && editor->hovered_y != -1) {
            update_editor_selected_entity(
                editor,
                Entity_Kind_Neutral_Tile,
                get_game_board_tile_type(
                    game_board, 
                    editor->hovered_x, 
                    editor->hovered_y
                ),
                TILE_VAR_NONE
            );
        }
    }
}

void render_game_editor(Game_Editor* editor)
{
    // SE_draw(editor->se, rend);
}

void free_game_editor(Game_Editor* editor)
{
    if (editor != NULL) {
        free(editor);
    }
}
