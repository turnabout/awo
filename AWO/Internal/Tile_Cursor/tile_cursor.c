#include <stdlib.h>

#include "AWO/types.h"
#include "Config/config.h"
#include "Tile_Cursor/tile_cursor.h"

Tile_Cursor* create_game_cursor(UI_Data* ui_data)
{
    Tile_Cursor* cursor = malloc(sizeof(Tile_Cursor));

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

void update_cursor(Tile_Cursor* cursor, Mouse_State* mouse, Camera* camera)
{
    int tile_x, tile_y;

    /*
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
     */
}

void update_cursor_style(Tile_Cursor* cursor, Tile_Cursor_Style style)
{
    switch (style) {
    case Tile_Cursor_Regular_Style:
        cursor->active_animation = cursor->animation_regular;
        break;
    case Tile_Cursor_X_Style:
        cursor->active_animation = cursor->animation_x;
        break;
    }
}

void render_game_cursor(Tile_Cursor* cursor, Extras_Renderer* renderer)
{
    /*
    if (cursor->shown) {
        queue_extra(renderer, cursor->dst, &cursor->active_animation->frames[0]);
    }
     */
}

void free_game_cursor(Tile_Cursor* cursor)
{
    if (cursor != NULL) {
        free(cursor);
    }
}