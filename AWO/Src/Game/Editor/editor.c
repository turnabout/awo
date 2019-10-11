#include <SDL.h>
#include "Game/Entities/Tile/enums.h"
#include "Game/Editor/UI/selected_entity.h"
#include "editor.h"

struct Editor {
    Game_Board* gb;

    // Currently selected tile
    Tile_Type selected_tile_type;
    Tile_Var selected_tile_var;

    // UI box showing the currently selected entity
    Selected_Entity* se;

    // Reference to the game's tiles data
    Tiles_Data* td;
};

Editor* create_editor(Game_Board* gb, Tiles_Data* td, int* screen_w, int* screen_h)
{
    Editor* editor = malloc(sizeof(Editor));

    editor->gb = gb;
    editor->td = td;
    editor->selected_tile_type = TILE_TYPE_DEFAULT;
    editor->selected_tile_var = TILE_VAR_DEFAULT;
    editor->se = SE_create(screen_w, screen_h);

    return editor;
}

// Apply autovar to tile at given game board coordinates
void apply_autovar(Editor* editor, int x, int y)
{
    Tile_Type middle_tile = GB_get_tile_type_at_coords(editor->gb, x, y);

    // No need to apply if middle tile is out of bounds
    if (middle_tile == OOB) {
        return;
    }

    GB_edit_tile(
        editor->gb, 
        editor->selected_tile_type, 

        TD_get_tile_auto_var(
            editor->td,
            middle_tile,
            GB_get_tile_type_at_coords(editor->gb, x, y - 1),
            GB_get_tile_type_at_coords(editor->gb, x + 1, y),
            GB_get_tile_type_at_coords(editor->gb, x, y + 1),
            GB_get_tile_type_at_coords(editor->gb, x - 1, y)
        ),

        x, 
        y
    );
}

// Adds a tile to game board at the current mouse coordinates.
void add_tile_at_mouse(Editor* editor, Mouse_State* mouse)
{
    // Get the board coordinates of the existant tile that was clicked
    int x, y;
    GB_get_pointer_board_coords(editor->gb, mouse->pointer, &x, &y);

    // TODO: ignore if clicked tile coordinates are the same as previously added one

    // Get the type of the clicked tile
    Tile_Type clicked_tile_type = GB_get_tile_type_at_coords(editor->gb, x, y);

    // Ignore if clicked out of bounds
    if (clicked_tile_type == OOB) {
        return;
    }

    // Place editor's selected tile with default tile type
    GB_edit_tile(
        editor->gb, 
        editor->selected_tile_type, 
        TD_get_tile_default_var(editor->td, clicked_tile_type), 
        x, 
        y
    );

    // Apply autovars to placed tile and its adjacent tiles
    apply_autovar(editor, x,     y);
    apply_autovar(editor, x - 1, y);
    apply_autovar(editor, x + 1, y);
    apply_autovar(editor, x,     y - 1);
    apply_autovar(editor, x,     y + 1);
}

void update_editor(Editor* editor, Mouse_State* mouse)
{
    if (mouse->in_window) {
        if (mouse_down_start(mouse, MOUSE_LEFT)) {
            add_tile_at_mouse(editor, mouse);
        }
    }

    SE_update(editor->se, mouse);
}

void draw_editor(Editor* editor, SDL_Renderer* rend)
{
    SE_draw(editor->se, rend);
}
