#include <stdlib.h>

#include "Game/Editor/game_editor.h"
#include "Game/Inputs/inputs.h"

typedef enum Game_Editor_Mode {
    GAME_EDITOR_MODE_NEUTRAL,
    GAME_EDITOR_MODE_DRAGGING,
} Game_Editor_Mode;

struct Game_Editor {

    // Coordinates of the previously-edited entity
    int entity_x, entity_y;

    // Currently selected tile type & variation
    int selected_entity_type, selected_entity_var;

    // Current mode
    Game_Editor_Mode mode;

    // Reference to the game's loaded game board
    Game_Board* game_board;

    // Reference to the game clock module
    Game_Clock* game_clock;

    // The mouse state module
    Mouse_State* mouse_state;

    // UI box showing the currently selected entity
    // Selected_Entity* selected_entity;
};

Game_Editor* create_game_editor(
    Game_Board* game_board, 
    Game_Clock* game_clock,
    Mouse_State* mouse_state
)
{
    Game_Editor* editor = malloc(sizeof(Game_Editor));

    editor->game_board = game_board;
    editor->game_clock = game_clock;

    editor->mode = GAME_EDITOR_MODE_NEUTRAL;

    editor->selected_entity_type = TILE_TYPE_NONE;
    editor->selected_entity_var = TILE_VAR_NONE;

    editor->entity_x = -1;
    editor->entity_y = -1;

    editor->mouse_state = mouse_state;

    // editor->selected_entity = SE_create(window_width, window_height);

    return editor;
}

// Apply autovar to tile at given game board coordinates
void apply_autovar(Game_Editor* editor, int x, int y)
{
    /*
    Tile_Type middle_tile_type = GB_get_tile_type_at_coords(editor->gb, x, y);

    // No need to apply if middle tile is out of bounds
    if (middle_tile_type == OOB) {
        return;
    }

    GB_edit_tile(
        editor->gb, 
        middle_tile_type, 

        TD_get_tile_auto_var(
            editor->td,
            middle_tile_type,
            GB_get_tile_type_at_coords(editor->gb, x, y - 1),
            GB_get_tile_type_at_coords(editor->gb, x + 1, y),
            GB_get_tile_type_at_coords(editor->gb, x, y + 1),
            GB_get_tile_type_at_coords(editor->gb, x - 1, y)
        ),

        x, 
        y
    );
    */
}

void update_editor_selected_tile_type(Game_Editor* editor, int type, int variation)
{
    printf("updating tile to: %s, %s\n", tile_type_str[type], tile_var_str[variation]);
    editor->selected_entity_type = type;
    editor->selected_entity_var = variation;
}

void update_game_editor(Game_Editor* editor, Game_Camera* camera)
{
    // Exit early if no entity type is selected
    if (editor->selected_entity_type == TILE_TYPE_NONE) {
        return;
    }

    if (editor->mouse_state->buttons[MOUSE_BUTTON_LEFT] == BUTTON_DOWN) {

        // Get coordinates of the clicked entity
        int entity_x = 0, entity_y = 0;

        if (!get_subject_grid_coordinates(
            camera,
            editor->mouse_state->x,
            editor->mouse_state->y,
            &entity_x,
            &entity_y
        )) {
            return;
        }

        // If the mouse was already held down on this grid tile, don't bother editing
        if (
            editor->mode == GAME_EDITOR_MODE_DRAGGING &&
            entity_x == editor->entity_x && 
            entity_y == editor->entity_y
        ) {
            return;
        }

        // Edit the entity at these coordinates
        // TODO: move into callback

        // If no variation, invalid if property
        int applied_variation = editor->selected_entity_var;

        // If no variation selected, use auto-vars to determine the variation to use
        if (applied_variation == TILE_VAR_NONE) {
            // TODO
            return;
        }

        // Update the game board tile at the given coordinates
        edit_game_board_tile(
            editor->game_board,
            editor->game_clock,
            editor->selected_entity_type,
            applied_variation,
            entity_x,
            entity_y
        );

        editor->entity_x = entity_x;
        editor->entity_y = entity_y;

        // Apply autovar to surrounding tiles
        // TODO

        // Set editor mode as dragging
        editor->mode = GAME_EDITOR_MODE_DRAGGING;

    } else if (editor->mode == GAME_EDITOR_MODE_DRAGGING) {

        // No longer dragging, reset editor mode
        editor->mode = GAME_EDITOR_MODE_NEUTRAL;
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
