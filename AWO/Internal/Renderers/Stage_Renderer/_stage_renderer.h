#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Render_Grid/render_grid.h"
#include "Renderers/Stage_Renderer/stage_renderer.h"
#include "Game_Data/game_data.h"

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

    // Shader program used to render the render-grids.
    GLuint grids_shader_program;

    // View matrix applied to tile render-grid layers.
    mat4 tiles_view;

    // View matrix applied to unit render-grid layers.
    mat4 units_view;

    // Render grid layers, used to render the main entities of the game (tiles, units, etc).
    Render_Grid* grid_layers[STAGE_GRID_LAYER_COUNT];

    // Empty tile frame, used to clear render grids.
    Frame* empty_frame;

    // Reference to the game data module.
    Game_Data* game_data;

};

/*! @brief Updates the stage renderer visual data for the tile at the given coordinates.
 *
 * @note Uses the internally stored stage that was given to the renderer through 
 * `create_stage_renderer`.
 *
 * @note Sets palette data to default non-fog values. Fog palette data must be manually set after
 * calling this.
 *
 *  @param[in] renderer The stage renderer module.
 *  @param[in] x X coordinate of the tile pixel to update.
 *  @param[in] y Y coordinate of the tile pixel to update.
 */
void update_stage_renderer_tile(Stage_Renderer* renderer, Uint8 x, Uint8 y);
