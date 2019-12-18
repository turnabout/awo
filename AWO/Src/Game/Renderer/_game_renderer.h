#pragma once

#include "Game/Renderer/game_renderer.h"
#include "Game/Renderer/Render_Grid/render_grid.h"

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

    // Layers of tile grids used to render tiles.
    Render_Grid* tile_grid_layers[TILE_LAYER_TYPE_COUNT];
};

/*! @brief Internally initializes and returns the game renderer.
 *
 *  @param[in] grid_width Initial width of the render grids.
 *  @param[in] grid_height Initial height of the render grids.
 *  @param[in] game_palette_texture Initial palette texture used by the game.
 *  @param[in] tiles_data The tiles data module.
 */
Game_Renderer* _init_game_renderer(
    int grid_width,
    int grid_height,
    GLuint game_palette_texture,
    Tiles_Data* tiles_data
);

/*! @brief Frees the memory occupied by the game renderer.
 *
 *  @param[in] renderer The game renderer module.
 */
void _free_game_renderer(Game_Renderer* renderer);
