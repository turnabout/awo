#include <stdlib.h>

#include "Game/Cursor/game_cursor.h"

struct Game_Cursor {

    // The cursor's animation.
    Animation* animation;

    // Whether the game cursor should be hidden.
    Bool hidden;

    // Current pixel coordinates of the cursor.
    vec2 dst;

    // Board coordinates of the currently hovered tile.
    int hovered_tile_x, hovered_tile_y;

    // Amount of pixels to offset the cursor position so it's centered around a tile.
    int center_offset_px;
};

Game_Cursor* create_game_cursor(UI_Data* ui_data)
{
    Game_Cursor* cursor = malloc(sizeof(Game_Cursor));

    cursor->animation = get_UI_element_frames(ui_data, TileCursor);
    cursor->hidden = TRUE;
    cursor->hovered_tile_x = cursor->hovered_tile_y = -1;

    // Calculate the cursor adjustment
    int diff = cursor->animation->frames[0].width - DEFAULT_ENTITY_SIZE;
    cursor->center_offset_px = diff / 2;

    return cursor;
}

void update_cursor(Game_Cursor* cursor, Mouse_State* mouse, Game_Camera* camera)
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
        cursor->hovered_tile_x = cursor->hovered_tile_y = -1;
        cursor->hidden = TRUE;
        return;
    }

    // Exit early if the hovered tile hasn't changed
    if (tile_x == cursor->hovered_tile_x && tile_y == cursor->hovered_tile_y) {
        return;
    }

    cursor->hovered_tile_x = tile_x;
    cursor->hovered_tile_y = tile_y;

    // Set the absolute coordinates to render the cursor, centered around the tile
    cursor->dst[0] = (float)((DEFAULT_ENTITY_SIZE * tile_x) - cursor->center_offset_px);
    cursor->dst[1] = (float)((DEFAULT_ENTITY_SIZE * tile_y) - cursor->center_offset_px);

    cursor->hidden = FALSE;
}

void hide_game_cursor(Game_Cursor* cursor)
{
    cursor->hidden = TRUE;
}

void render_game_cursor(Game_Cursor* cursor, Game_Renderer* renderer)
{
    if (!cursor->hidden) {
        queue_extra(renderer, cursor->dst, &cursor->animation->frames[0]);
    }
}

void free_game_cursor(Game_Cursor* cursor)
{
    if (cursor != NULL) {
        free(cursor);
    }
}