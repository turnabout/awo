#include <SDL.h>
#include "editor.h"
#include "Visuals/Data/Tiles/tiles_enums.h"

struct Editor {
    Game_Board* gb;

    // Currently selected tile
    Tile_Type selected_tile_type;
    Tile_Var selected_tile_var;
};

Editor* create_editor(Game_Board* gb)
{
    Editor* editor = malloc(sizeof(Editor));

    editor->gb = gb;
    editor->selected_tile_type = DEFAULT_TILE_TYPE;
    editor->selected_tile_var = DEFAULT_TILE_VAR;

    return editor;
}

void update_editor(Editor* editor, Mouse_State* mouse)
{
    if (mouse->in_window) {
        if (click_down(mouse, MOUSE_LEFT)) {
            // Update tile at given coordinates with the new type/variation
            GB_edit_tile_pointer_coords(
                editor->gb,
                editor->selected_tile_type,
                editor->selected_tile_var,
                mouse->pointer
            );
        }
    }
}

void draw_editor(Editor* editor, SDL_Renderer* rend)
{
    // TODO
}
