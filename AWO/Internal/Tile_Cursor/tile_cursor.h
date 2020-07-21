#pragma once

#include "Camera/camera.h"
#include "Game_Data/UI_Data/UI_data.h"
#include "Renderers/Extras_Renderer/extras_renderer.h"
#include "Input_State/Mouse_State/mouse_state.h"

typedef enum Tile_Cursor_Style {
    Tile_Cursor_Regular_Style,
    Tile_Cursor_X_Style,
} Tile_Cursor_Style;

/*! @brief Tile cursor, highlighting the tile currently hovered on by the player.
 */
typedef struct Tile_Cursor {

    // The cursor's animation.
    Animation* active_animation;
    Animation* animation_regular;
    Animation* animation_x;

    // Whether the game cursor should be shown.
    Bool shown;

    // Current pixel coordinates of the cursor.
    vec2 dst;

    // Board coordinates of the currently hovered tile.
    int hovered_x, hovered_y;

    // Amount of pixels to offset the cursor position so it's centered around a tile.
    int center_offset_px;

} Tile_Cursor;

Tile_Cursor* create_game_cursor(UI_Data* ui_data);
void update_cursor_style(Tile_Cursor* cursor, Tile_Cursor_Style style);
void update_cursor(Tile_Cursor* cursor, Mouse_State* mouse, Camera* camera);
void render_game_cursor(Tile_Cursor* cursor, Extras_Renderer* renderer);
void free_game_cursor(Tile_Cursor* cursor);
