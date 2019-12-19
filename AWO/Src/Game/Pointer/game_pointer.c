#include <stdlib.h>

#include "Game/Pointer/game_pointer.h"

struct Game_Pointer {

    // The pointer's animation.
    Animation* animation;

    // Whether the game pointer should be hidden.
    Bool hidden;

    // Current pixel coordinates of the pointer.
    int x, y;
};

Game_Pointer* create_game_pointer(UI_Data* ui_data)
{
    Game_Pointer* pointer = malloc(sizeof(Game_Pointer));

    pointer->animation = get_UI_element_frames(ui_data, TileCursor);
    pointer->hidden = FALSE;

    return pointer;
}

void update_pointer(Game_Pointer* pointer, Mouse_State* mouse, Game_Camera* camera)
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
        pointer->hidden = TRUE;
        return;
    }

    // Mouse is hovering a tile - get the absolute coordinates where we should render the pointer
    // int board_pixel_w, board_pixel_h;
    // get_subject_pixel_dimensions(camera, &board_pixel_w, &board_pixel_h);

    pointer->hidden = FALSE;
}

void hide_game_pointer(Game_Pointer* pointer)
{
    pointer->hidden = TRUE;
}

void render_game_pointer(Game_Pointer* pointer, Game_Renderer* renderer)
{
    // queue_extra(game->renderer, (vec2) { 85.0, 0.0 }, frame);
}

void free_game_pointer(Game_Pointer* pointer)
{
    if (pointer != NULL) {
        free(pointer);
    }
}