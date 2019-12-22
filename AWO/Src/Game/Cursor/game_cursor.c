#include <stdlib.h>

#include "Game/Cursor/game_cursor.h"

struct Game_Cursor {

    // The pointer's animation.
    Animation* animation;

    // Whether the game pointer should be hidden.
    Bool hidden;

    // Current pixel coordinates of the pointer.
    vec2 dst;

    // Board coordinates of the currently hovered tile.
    int hovered_tile_x, hovered_tile_y;

    // Amount of pixels to offset the pointer position so it's centered around a tile.
    int center_offset_px;
};

Game_Cursor* create_game_cursor(UI_Data* ui_data)
{
    Game_Cursor* pointer = malloc(sizeof(Game_Cursor));

    pointer->animation = get_UI_element_frames(ui_data, TileCursor);
    pointer->hidden = TRUE;
    pointer->hovered_tile_x = pointer->hovered_tile_y = -1;

    // Calculate the pointer adjustment
    int diff = pointer->animation->frames[0].width - DEFAULT_ENTITY_SIZE;
    pointer->center_offset_px = diff / 2;

    return pointer;
}

void update_cursor(Game_Cursor* pointer, Mouse_State* mouse, Game_Camera* camera)
{
    int tile_x, tile_y;

    // Exit early if mouse is not hovering a grid tile
    if (!get_subject_grid_coordinates(
        camera,
        mouse->x,
        mouse->y,
        &tile_x,
        &tile_y
    )) {
        pointer->hovered_tile_x = pointer->hovered_tile_y = -1;
        pointer->hidden = TRUE;
        return;
    }

    // Exit early if the hovered tile hasn't changed
    if (tile_x == pointer->hovered_tile_x && tile_y == pointer->hovered_tile_y) {
        return;
    }

    pointer->hovered_tile_x = tile_x;
    pointer->hovered_tile_y = tile_y;

    // Set the absolute coordinates to render the pointer, centered around the tile
    pointer->dst[0] = (float)((DEFAULT_ENTITY_SIZE * tile_x) - pointer->center_offset_px);
    pointer->dst[1] = (float)((DEFAULT_ENTITY_SIZE * tile_y) - pointer->center_offset_px);

    pointer->hidden = FALSE;
}

void hide_game_cursor(Game_Cursor* pointer)
{
    pointer->hidden = TRUE;
}

void render_game_cursor(Game_Cursor* pointer, Game_Renderer* renderer)
{
    if (!pointer->hidden) {
        queue_extra(renderer, pointer->dst, &pointer->animation->frames[0]);
    }
}

void free_game_cursor(Game_Cursor* pointer)
{
    if (pointer != NULL) {
        free(pointer);
    }
}