#pragma once

#include "Game/Renderer/game_renderer.h"
#include "Game/Renderer/Render_Grid/render_grid.h"
#include "Game/Renderer/Extras_Renderer/extras_renderer.h"

struct Game_Renderer {

    // Dimensions of the raw sprite sheet
    int sprite_sheet_width, sprite_sheet_height;

    // Tile shader program.
    GLuint tiles_shader_program;

    // Texture containing the game's raw sprite sheet.
    GLuint sprite_sheet_texture;

    // Texture containing palettes.
    GLuint game_palette_texture;

    // Reference to the empty tile frame, used to "clear" render grid tiles.
    Animation* empty_tile_frame;

    // Render grid layers, used to render the main entities of the game (tiles, units, etc).
    Render_Grid* grid_layers[TILE_LAYER_TYPE_COUNT];

    // Module used to render extra elements on top of the grid layers.
    Extras_Renderer* extras_renderer;
};
