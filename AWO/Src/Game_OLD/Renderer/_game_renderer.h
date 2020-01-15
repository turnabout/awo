#pragma once

#include "Game/Renderer/game_renderer.h"
#include "Game/Renderer/Render_Grid/render_grid.h"
#include "Game/Renderer/Extras_Renderer/extras_renderer.h"

struct Game_Renderer {

    // Dimensions of the raw sprite sheet
    int sprite_sheet_width, sprite_sheet_height;

    // Texture containing the game's raw sprite sheet.
    GLuint sprite_sheet_texture;

    // Texture containing palettes.
    GLuint game_palette_texture;

    // Render grid tile layers shader program & view matrix.
    GLuint grid_shader;

    // View matrix applied to tile grid layers.
    mat4 tiles_view;

    // View matrix applied to unit grid layers.
    mat4 units_view;

    // Render grid layers, used to render the main entities of the game (tiles, units, etc).
    Render_Grid* grid_layers[GRID_LAYER_COUNT];

    // Reference to the empty tile frame, used to "clear" render grid pixels.
    Animation* empty_tile_frame;

    // Module used to render extra elements on top of the grid layers.
    Extras_Renderer* extras_renderer;
};
