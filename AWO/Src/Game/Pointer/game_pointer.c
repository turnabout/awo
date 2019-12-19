#include <stdlib.h>

#include "Game/Pointer/game_pointer.h"

struct Pointer {

    // The pointer's animation.
    Animation* animation;

    // Current pixel coordinates of the pointer.
    int x, y;
};

Pointer* create_pointer(UI_Data* ui_data)
{
    Pointer* pointer = malloc(sizeof(Pointer));

    pointer->animation = get_UI_element_frames(ui_data, TileCursor);
    

    return pointer;
}

void update_pointer(Pointer* pointer, Mouse_State* mouse, Game_Camera* camera)
{
    int tile_x, tile_y;

    // Exit early if mouse is not hovering a grid tile
    if (!get_subject_tile_by_coordinates(
        camera,
        mouse->x,
        mouse->y,
        &tile_x,
        &tile_y
    )) {
        return;
    }

    // Mouse is hovering a tile - get the absolute coordinates where we should render the pointer
    // int board_pixel_w, board_pixel_h;
    // get_subject_pixel_dimensions(camera, &board_pixel_w, &board_pixel_h);

}

void render_pointer(Pointer* pointer, Game_Renderer* renderer)
{
}

void free_pointer(Pointer* pointer)
{
    if (pointer != NULL) {
        free(pointer);
    }
}