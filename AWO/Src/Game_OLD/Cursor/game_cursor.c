#include <stdlib.h>

#include "Game/Cursor/game_cursor.h"

Game_Cursor* create_game_cursor(UI_Data* ui_data)
{
    Game_Cursor* cursor = malloc(sizeof(Game_Cursor));

    if (cursor == NULL) {
        return NULL;
    }

    cursor->animation_regular = get_UI_element_frames(ui_data, TileCursor);
    cursor->animation_x = get_UI_element_frames(ui_data, TileCursorX);
    cursor->active_animation = cursor->animation_regular;

    cursor->shown = FALSE;
    cursor->hovered_x = cursor->hovered_y = -1;

    // Calculate the cursor adjustment
    int diff = cursor->animation_regular->frames[0].width - DEFAULT_ENTITY_SIZE;
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
        cursor->hovered_x = cursor->hovered_y = -1;
        cursor->shown = FALSE;
        return;
    }

    // Exit early if the hovered tile hasn't changed
    if (tile_x == cursor->hovered_x && tile_y == cursor->hovered_y) {
        return;
    }

    cursor->hovered_x = tile_x;
    cursor->hovered_y = tile_y;

    // Set the absolute coordinates to render the cursor, centered around the tile
    cursor->dst[0] = (float)((DEFAULT_ENTITY_SIZE * tile_x) - cursor->center_offset_px);
    cursor->dst[1] = (float)((DEFAULT_ENTITY_SIZE * tile_y) - cursor->center_offset_px);

    cursor->shown = TRUE;
}

void update_cursor_style(Game_Cursor* cursor, Game_Cursor_Style style)
{
    switch (style) {
    case Game_Cursor_Regular_Style:
        cursor->active_animation = cursor->animation_regular;
        break;
    case Game_Cursor_X_Style:
        cursor->active_animation = cursor->animation_x;
        break;
    }
}

void render_game_cursor(Game_Cursor* cursor, Game_Renderer* renderer)
{
    if (cursor->shown) {
        queue_extra(renderer, cursor->dst, &cursor->active_animation->frames[0]);
    }
}

void free_game_cursor(Game_Cursor* cursor)
{
    if (cursor != NULL) {
        free(cursor);
    }
}