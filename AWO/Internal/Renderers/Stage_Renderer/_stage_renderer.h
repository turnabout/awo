#pragma once

#include <cglm/cglm.h>

#include "Game/Renderer/Render_Grid/render_grid.h"
#include "Game/Renderer/Stage_Renderer/stage_renderer.h"

/*! @brief Grid layers of the stage renderer.
 */
typedef enum Stage_Grid_Layer {

    // Tile layers
    TILE_LAYER_0,
    TILE_LAYER_1,

    // Unit layers
    UNIT_LAYER,
    UNIT_HP_LAYER,
    UNIT_AMMO_FUEL_LAYER,
    UNIT_STATUS_LAYER,
} Stage_Grid_Layer;

#define STAGE_TILE_LAYER_COUNT 2
#define STAGE_UNIT_LAYER_COUNT 1 // TODO: update when we add unit metadata layers
#define STAGE_GRID_LAYER_COUNT STAGE_TILE_LAYER_COUNT + STAGE_UNIT_LAYER_COUNT

struct Stage_Renderer {

    // Reference to the stage this module renders.
    Stage* stage;

    // Texture containing the game's raw sprite sheet.
    GLuint sprite_sheet_texture;

    // Texture containing palettes.
    GLuint palette_texture;

    // Render grid tile layers shader program & view matrix.
    GLuint shader;

    // View matrix applied to tile grid layers.
    mat4 tiles_view;

    // View matrix applied to unit grid layers.
    mat4 units_view;

    // Render grid layers, used to render the main entities of the game (tiles, units, etc).
    Render_Grid* grid_layers[STAGE_GRID_LAYER_COUNT];

    // Empty tile frame, used to clear render grids.
    Frame* empty_frame;

};