#include <stdlib.h>

#include "Game/Editor/_game_editor.h"

Game_Editor* create_game_editor(int* window_width, int* window_height)
{
    Game_Editor* editor = malloc(sizeof(Game_Editor));

    editor->mode = Editor_Mode_Neutral;
    editor->update_cb = NULL;

    editor->selected_entity_type = TILE_TYPE_NONE;
    editor->selected_entity_var = TILE_VAR_NONE;

    editor->selected_entity_type = Plain;
    editor->selected_entity_var = Default;

    editor->entity_x = -1;
    editor->entity_y = -1;

    // Start with default edited type of neutral tile
    // TODO: remove, should be set from outside
    update_editor_entity_type(editor, Editor_Entity_Type_Neutral_Tile);

    // editor->selected_entity = SE_create(window_width, window_height);

    return editor;
}

void update_editor_selected_entity(Game_Editor* editor, int type, int variation)
{
    printf("updating tile to: %s, %s\n", tile_type_str[type], tile_var_str[variation]);
    editor->selected_entity_type = type;
    editor->selected_entity_var = variation;
}

void update_editor_entity_type(Game_Editor* editor, Game_Editor_Entity_Type new_type)
{
    switch (new_type) {
    case Editor_Entity_Type_Neutral_Tile:
        editor->update_cb = set_neutral_tile_entity;
        break;
    case Editor_Entity_Type_Property_Tile:
        editor->update_cb = set_property_tile_entity;
        break;
    case Editor_Entity_Type_Unit:
        editor->update_cb = set_unit_entity;
        break;

    default:
        // TODO: error
        break;
    }
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
        if (editor->selected_entity_type == TILE_TYPE_NONE || editor->update_cb == NULL) {
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

        editor->update_cb(editor, game_board, game_clock);
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
