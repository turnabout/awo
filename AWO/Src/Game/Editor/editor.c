#include <stdlib.h>

#include "Game/Editor/editor.h"
#include "Game/Inputs/inputs.h"

struct Editor {

    // Coordinates of the previously-edited tile
    int prev_edited_tile_x, prev_edited_tile_y;

    // Currently selected tile
    Tile_Type selected_tile_type;
    int selected_tile_var;

    // Reference to the game's loaded game board
    Game_Board* game_board;

    // Reference to the game clock module
    Game_Clock* game_clock;

    // Reference to the tiles data module
    Tiles_Data* tiles_data;

    // Pointer to the window dimensions
    int* window_width, * window_height;

    // UI box showing the currently selected entity
    // Selected_Entity* selected_entity;
};

Editor* create_editor(
    Game_Board* game_board, 
    Tiles_Data* tiles_data, 
    Game_Clock* game_clock,
    int* window_width, 
    int* window_height
)
{
    Editor* editor = malloc(sizeof(Editor));

    editor->game_board = game_board;
    editor->tiles_data = tiles_data;

    editor->selected_tile_type = River;
    editor->selected_tile_var = TILE_VAR_NONE;

    editor->prev_edited_tile_x = -1;
    editor->prev_edited_tile_y = -1;

    editor->window_width = window_width;
    editor->window_height = window_height;

    // editor->selected_entity = SE_create(window_width, window_height);

    return editor;
}

// Apply autovar to tile at given game board coordinates
void apply_autovar(Editor* editor, int x, int y)
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

// Adds a tile to game board at the current mouse coordinates.
void edit_tile_at_mouse(Editor* editor)
{

    /*
    // Get the board coordinates of the existant tile that was clicked
    int x, y;
    GB_get_pointer_board_coords(editor->gb, mouse->pointer, &x, &y);

    // Ignore if clicked out of bounds or if clicked tile coordinates the same as previous
    if (
        (editor->prev_edited_tile_x == x && editor->prev_edited_tile_y == y) ||
        GB_get_tile_type_at_coords(editor->gb, x, y) == OOB
    ) {
        return;
    }

    // Place editor's selected tile with default tile type
    GB_edit_tile(
        editor->gb, 
        editor->selected_tile_type, 
        TD_get_tile_default_var(editor->td, editor->selected_tile_type), 
        x, 
        y
    );

    // Apply autovars to placed tile and its adjacent tiles
    apply_autovar(editor, x,     y);
    apply_autovar(editor, x - 1, y);
    apply_autovar(editor, x + 1, y);
    apply_autovar(editor, x,     y - 1);
    apply_autovar(editor, x,     y + 1);

    // Set coordinates of previously edited tile
    editor->prev_edited_tile_x = x;
    editor->prev_edited_tile_y = y;
    */
}

void update_editor_selected_tile_type(Editor* editor, Tile_Type type, int variation)
{
    editor->selected_tile_type = type;
}

void update_editor(Editor* editor)
{
    // int mouse_x, mouse_y;

    // if (*editor->window_width)

    /*
    if (mouse->in_window) {
        if (mouse_down(mouse, MOUSE_LEFT)) {
            edit_tile_at_mouse(editor, mouse);
        }
    }

    SE_update(editor->se, mouse);
    */
}

void render_editor(Editor* editor)
{
    // SE_draw(editor->se, rend);
}
