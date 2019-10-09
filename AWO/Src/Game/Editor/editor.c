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

void update_editor(Editor* editor, Mouse_State* mouse)
{
    if (mouse->in_window) {
        if (mouse_down_start(mouse, MOUSE_LEFT)) {
            // Update tile at given coordinates with the new type/variation
            int x, y;

            GB_get_pointer_board_coords(editor->gb, mouse->pointer, &x, &y);
            Tile_Type clicked_tile_type = GB_get_tile_type_at_coords(editor->gb, x, y);

            printf("clicked tile type: %s\n", tile_type_str[clicked_tile_type]);
        }
    }

    SE_update(editor->se, mouse);
}

void draw_editor(Editor* editor, SDL_Renderer* rend)
{
    SE_draw(editor->se, rend);
}
