#pragma once

#include "Internal/Camera/camera.h"
#include "Game/Data/UI/UI_data.h"
#include "Game/Inputs/Mouse/mouse.h"
#include "Game/Renderer/game_renderer.h"

typedef enum Game_Cursor_Style {
    Game_Cursor_Regular_Style,
    Game_Cursor_X_Style,
} Game_Cursor_Style;

/*! @brief Tile cursor, highlighting the tile currently hovered on by the player.
 */
typedef struct Game_Cursor {

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

} Game_Cursor;

Game_Cursor* create_game_cursor(UI_Data* ui_data);
void update_cursor_style(Game_Cursor* cursor, Game_Cursor_Style style);
void update_cursor(Game_Cursor* cursor, Mouse_State* mouse, Camera* camera);
void render_game_cursor(Game_Cursor* cursor, Game_Renderer* renderer);
void free_game_cursor(Game_Cursor* cursor);
