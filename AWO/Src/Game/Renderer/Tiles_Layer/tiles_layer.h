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

/*! @brief Render this tiles layer.
 *
 *  @param[in] tiles_layer The tiles layer struct.
 */
void render_tiles_layer(Tiles_Layer* tiles_layer);

/*! @brief Update a pixel's value in the tiles layer's tiles texture.
 *
 *  @param[in] tiles_layer The tiles layer to update.
 *  @param[in] x X offset of the pixel to update.
 *  @param[in] y Y offset of the pixel to update.
 *  @param[in] value The value used to update with.
 */
void update_tiles_layer_pixel(Tiles_Layer* tiles_layer, GLuint x, GLuint y, vec4 value);

void update_tiles_layer_pixel_low(Tiles_Layer* tiles_layer, GLuint x, GLuint y, vec2 values);

/*! @brief Fill pixels' values in the tiles layer's tiles texture.
 *
 *  @param[in] tiles_layer The tiles layer to update.
 *  @param[in] value The value used to update with.
 */
void fill_tiles_layer_pixels(Tiles_Layer* tiles_layer, vec4 value);

/*! @brief Get the VAO used by tiles layers.
 *
 *  @param[in] tiles_layer The tiles layer to update.
 */
void free_tiles_layer(Tiles_Layer* tiles_layer);

/*! @brief Get the VAO used by tiles layers.
 *
 *  @param[in] tile_layers_width The width taken up by the tiles texture.
 *  @param[in] tile_layers_height The height taken up by the tiles texture.
 *  @return The tiles layers VAO.
 */
GLuint get_tiles_layers_VAO(int tile_layers_width, int tile_layers_height);
