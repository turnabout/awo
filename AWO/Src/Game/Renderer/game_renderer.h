#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include "Game/Data/Tile/tiles_data.h"

typedef struct Game_Renderer Game_Renderer;

typedef enum Tile_Layer_Index {

    // Tile layers
    TILE_LAYER_0,
    TILE_LAYER_1,

    // Unit layer
    UNIT_LAYER,

    // Unit metadata layers
    UNIT_HP_LAYER,
    UNIT_AMMO_FUEL_LAYER,
    UNIT_STATUS_LAYER,
} Tile_Layer_Index;

#define TILE_LAYER_TYPE_COUNT TILE_LAYER_1 + 1 // TODO: change when we add unit layers

/*! @brief Initializes the game's renderer module.
 *
 *  @param[in] grid_width Initial width of the render grids.
 *  @param[in] grid_height Initial height of the render grids.
 *  @param[in] game_palette_texture Initial palette texture used by the game.
 *  @param[in] tiles_data The tiles data module.
 *  @param[in] window_width The window's initial width.
 *  @param[in] window_height The window's initial height.
 *  @returns The created game renderer module.
 */
Game_Renderer* create_game_renderer(
    int grid_width,
    int grid_height,
    GLuint game_palette_texture,
    Tiles_Data* tiles_data,
    int window_width,
    int window_height
);

/*! @brief Renders the game renderer's contents.
 */
void render_game_renderer_grids(Game_Renderer* renderer);

/*! @brief Update the game renderer's view matrices using the given view coordinates.
 *
 *  @param[in] renderer The game renderer.
 *  @param[in] view_x The view's X position.
 *  @param[in] view_y The view's X position.
 *  @param[in] view_zoom The view's zoom value.
 */
void update_game_renderer_view_matrices(
    Game_Renderer* renderer,
    int view_x,
    int view_y,
    float view_zoom
);

/*! @brief Update the game renderer's projection matrices.
 *
 *  @param[in] renderer The game renderer.
 *  @param[in] window_width The game window's width.
 *  @param[in] window_height The game window's height.
 */
void update_game_renderer_projection_matrices(
    Game_Renderer* renderer,
    int window_width,
    int window_height
);

/*! @brief Clear a pixel in the game renderer's tile layers.
 *
 *  @param[in] renderer The game renderer.
 *  @param[in] x X coordinate of the pixel to clear.
 *  @param[in] y Y coordinate of the pixel to clear.
 */
void clear_tile_layers_pixel(Game_Renderer* renderer, Uint8 x, Uint8 y);

/*! @brief Update a pixel's value in a render grid layer's tile texture.
 *
 *  @param[in] renderer The game renderer.
 *  @param[in] layer Which layer to update.
 *  @param[in] x X offset of the pixel to update.
 *  @param[in] y Y offset of the pixel to update.
 *  @param[in] value The value used to update with.
 */
void update_tile_layer_pixel(Game_Renderer* renderer, Tile_Layer_Index layer, Uint8 x, Uint8 y, vec4 value);
void update_tile_layer_pixel_high(Game_Renderer* renderer, Tile_Layer_Index layer, Uint8 x, Uint8 y, vec2 value);
void update_tile_layer_pixel_low(Game_Renderer* renderer, Tile_Layer_Index layer, Uint8 x, Uint8 y, vec2 value);

void queue_extra(Game_Renderer* renderer, vec2 dst, Frame* frame);
void render_extras(Game_Renderer* renderer);

/*! @brief Frees the memory occupied by the game renderer.
 *
 *  @param[in] renderer The game renderer.
 */
void free_game_renderer(Game_Renderer* renderer);
