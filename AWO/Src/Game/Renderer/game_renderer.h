#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include "Game/Data/Tile/tiles_data.h"

typedef struct Game_Renderer Game_Renderer;

typedef enum Tile_Layer_Type {
    TILE_LAYER_0,
    TILE_LAYER_1,
} Tile_Layer_Type;

#define TILE_LAYER_TYPE_COUNT TILE_LAYER_1 + 1

Game_Renderer* create_game_renderer(
    int tile_layers_width, 
    int tile_layers_height, 
    GLuint palettes_texture,
    Tiles_Data* tiles_data
);

/*! @brief Update one of the matrices used by the game renderer to render objects.
 *
 *  @param[in] renderer The game renderer object.
 *  @param[in] matrix The new matrix.
 *  @param[in] matrix_str The string representing the matrix to update ("view"|"projection").
 */
void update_game_renderer_matrix(Game_Renderer* renderer, mat4 matrix, const char* matrix_str);

/*! @brief Render the game renderer's tiles layers.
 *
 *  @param[in] renderer The game renderer object.
 */
void render_tiles_layers(Game_Renderer* renderer);

/*! @brief Update a pixel's value in a tiles layer's tiles texture.
 *
 *  @param[in] renderer The game's renderer.
 *  @param[in] layer Which layer to update.
 *  @param[in] x X offset of the pixel to update.
 *  @param[in] y Y offset of the pixel to update.
 *  @param[in] value The value used to update with.
 */
void update_renderer_tiles_layer_pixel(
    Game_Renderer* renderer, 
    Tile_Layer_Type layer,
    GLuint x, 
    GLuint y, 
    vec4 value
);

void free_game_renderer(Game_Renderer* renderer);
