#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

typedef struct Game_Renderer Game_Renderer;

typedef enum Tile_Layer_Type {
    TILE_LAYER_0,
    TILE_LAYER_1,
} Tile_Layer_Type;

#define TILE_LAYER_TYPE_COUNT TILE_LAYER_1 + 1

Game_Renderer* create_game_renderer(
    int tile_layers_width, 
    int tile_layers_height, 
    GLuint palettes_texture
);

/*! @brief Update one of the matrices used by the game renderer to render objects.
 *
 *  @param[in] renderer The game renderer object.
 *  @param[in] matrix The new matrix.
 *  @param[in] matrix_str The string representing the matrix to update ("view"|"projection").
 */
void update_game_renderer_matrix(Game_Renderer* renderer, mat4 matrix, const char* matrix_str);

void render_game_renderer(Game_Renderer* renderer);

void free_game_renderer(Game_Renderer* renderer);
