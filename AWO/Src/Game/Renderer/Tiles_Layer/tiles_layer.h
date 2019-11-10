#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/types.h>

typedef struct Tiles_Layer Tiles_Layer;

/*! @brief 
 *
 *  @param[in] tiles_width
 *  @param[in] tiles_height
 *  @return The created tiles layer.
 */
Tiles_Layer* create_tiles_layer(GLuint tiles_layer_width, GLuint tiles_layer_height);

void render_tiles_layer(Tiles_Layer* tiles_layer);

void update_tiles_layer_mem(Tiles_Layer* tiles_layer, GLuint x, GLuint y, vec4 values);

void fill_tiles_layer_mem(Tiles_Layer* renderer, vec4 values);

/*! @brief Get the VAO used by tiles layers.
 *
 *  @param[in] tile_layers_width The width taken up by the tiles texture.
 *  @return The tiles layers VAO.
 */
void free_tiles_layer(Tiles_Layer* tiles_layer);

/*! @brief Get the VAO used by tiles layers.
 *
 *  @param[in] tile_layers_width The width taken up by the tiles texture.
 *  @param[in] tile_layers_height The height taken up by the tiles texture.
 *  @return The tiles layers VAO.
 */
GLuint get_tiles_layers_VAO(int tile_layers_width, int tile_layers_height);
