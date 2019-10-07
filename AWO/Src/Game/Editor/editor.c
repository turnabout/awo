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
};

Editor* create_editor(Game_Board* gb, int* screen_w, int* screen_h)
{
    Editor* editor = malloc(sizeof(Editor));

    editor->gb = gb;
    editor->selected_tile_type = TILE_TYPE_DEFAULT;
    editor->selected_tile_var = TILE_VAR_DEFAULT;
    editor->se = SE_create(screen_w, screen_h);

    return editor;
}

void update_editor(Editor* editor, Mouse_State* mouse)
{
    if (mouse->in_window) {
        if (mouse_down(mouse, MOUSE_LEFT)) {
            // Update tile at given coordinates with the new type/variation
            GB_edit_tile_pointer_coords(
                editor->gb,
                editor->selected_tile_type,
                editor->selected_tile_var,
                mouse->pointer
            );
        }
    }

    SE_update(editor->se, mouse);
}

void draw_editor(Editor* editor, SDL_Renderer* rend)
{
    SE_draw(editor->se, rend);
}
