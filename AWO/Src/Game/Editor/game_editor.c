#include <stdlib.h>

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

    // Start with default editing values
    // TODO: remove, should be set from outside
    update_editor_selected_entity(editor, Editor_Entity_Type_Tile, Plain, SELECTED_ENTITY_VAR_NONE);

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

        if (type >= PROPERTY_TILE_TYPE_FIRST || type <= PROPERTY_TILE_TYPE_LAST) {

            editor->selected_entity_update_cb = set_editor_tile_entity;
        } else {
            editor->selected_entity_update_cb = set_editor_property_entity;
        }

    } else if (kind == Editor_Entity_Type_Unit) {
        editor->selected_entity_update_cb = set_editor_unit_entity;
    } else {
        // TODO: error
        editor->selected_entity_type = SELECTED_ENTITY_TYPE_NONE;
        editor->selected_entity_var = SELECTED_ENTITY_VAR_NONE;
        return;
    }

    // Set the selected entity's type and variation
    editor->selected_entity_type = type;
    editor->selected_entity_var = variation;
}

void update_game_editor(
    Game_Editor* editor, 
    Game_Renderer* game_renderer,
    Game_Camera* game_camera,
    Game_Board* game_board,
    Game_Clock* game_clock,
    Mouse_State* mouse_state
)
{
    if (mouse_state->buttons[MOUSE_BUTTON_LEFT] == BUTTON_DOWN) {

        // Exit early if no entity type is selected or not update callback is set
        if (
            editor->selected_entity_type == SELECTED_ENTITY_TYPE_NONE || 
            editor->selected_entity_update_cb == NULL
        ) {
            return;
        }

        // Get coordinates of the clicked entity
        int entity_x = 0, entity_y = 0;

        if (!get_subject_grid_coordinates(
            game_camera,
            mouse_state->x,
            mouse_state->y,
            &entity_x,
            &entity_y
        )) {
            return;
        }

        // If the mouse was already held down on this grid tile, don't bother editing
        if (
            editor->mode == Editor_Mode_Dragging &&
            entity_x == editor->entity_x && 
            entity_y == editor->entity_y
        ) {
            return;
        }

        // Edit the entity at these coordinates
        editor->entity_x = entity_x;
        editor->entity_y = entity_y;

        editor->selected_entity_update_cb(editor, game_board, game_clock);
        editor->mode = Editor_Mode_Dragging;

    } else if (editor->mode == Editor_Mode_Dragging) {

        // No longer dragging, reset editor mode
        editor->mode = Editor_Mode_Neutral;
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
