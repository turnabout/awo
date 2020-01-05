#pragma once

#include "Game/Data/UI/UI_data.h"
#include "Game/Inputs/Mouse/mouse.h"
#include "Game/Camera/game_camera.h"
#include "Game/Renderer/game_renderer.h"

/*! @brief Tile cursor, highlighting the tile currently hovered on by the player.
 */
typedef struct Game_Cursor {

    // The cursor's animation.
    Animation* animation;

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
void update_cursor(Game_Cursor* pointer, Mouse_State* mouse, Game_Camera* camera);
void render_game_cursor(Game_Cursor* pointer, Game_Renderer* renderer);
void free_game_cursor(Game_Cursor* pointer);
