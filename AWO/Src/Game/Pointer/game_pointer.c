#include <stdlib.h>

#include "Game/Pointer/game_pointer.h"

struct Game_Pointer {

    // The pointer's animation.
    Animation* animation;

    // Whether the game pointer should be hidden.
    Bool hidden;

    // Current pixel coordinates of the pointer.
    vec2 dst;

    // Board coordinates of the currently hovered tile.
    int tile_x, tile_y;

    // Amount of pixels to offset the pointer position so it's centered around a tile.
    int center_offset_px;
};

Game_Pointer* create_game_pointer(UI_Data* ui_data)
{
    Game_Pointer* pointer = malloc(sizeof(Game_Pointer));

    pointer->animation = get_UI_element_frames(ui_data, TileCursor);
    pointer->hidden = TRUE;
    pointer->tile_x = pointer->tile_y = -1;

    // Calculate the pointer adjustment
    int diff = pointer->animation->frames[0].width - DEFAULT_TILE_SIZE;
    pointer->center_offset_px = diff / 2;

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

    // Exit early if the hovered tile hasn't changed
    if (tile_x == pointer->tile_x && tile_y == pointer->tile_y) {
        return;
    }

    pointer->tile_x = tile_x;
    pointer->tile_y = tile_y;

    // Set the absolute coordinates to render the pointer, centered around the tile
    pointer->dst[0] = (float)((DEFAULT_TILE_SIZE * tile_x) - pointer->center_offset_px);
    pointer->dst[1] = (float)((DEFAULT_TILE_SIZE * tile_y) - pointer->center_offset_px);

    pointer->hidden = FALSE;
}

void hide_game_pointer(Game_Pointer* pointer)
{
    pointer->hidden = TRUE;
}

void render_game_pointer(Game_Pointer* pointer, Game_Renderer* renderer)
{
    if (!pointer->hidden) {
        queue_extra(renderer, pointer->dst, &pointer->animation->frames[0]);
    }
}

void free_game_pointer(Game_Pointer* pointer)
{
    if (pointer != NULL) {
        free(pointer);
    }
}