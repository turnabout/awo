#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/types.h>

#include "types.h"

typedef struct Tiles_Layer Tiles_Layer;

/*! @brief 
 *
 *  @param[in] tiles_width
 *  @param[in] tiles_height
 *  @return The created tiles layer.
 */
Tiles_Layer* create_tiles_layer(GLuint tiles_layer_width, GLuint tiles_layer_height);

/*! @brief Renders this tiles layer.
 *
 *  @param[in] tiles_layer The tiles layer struct.
 */
void render_tiles_layer(Tiles_Layer* tiles_layer);

/*! @brief Binds the tile texture associated with this tiles layer.
 *
 *  @param[in] tiles_layer The tiles layer struct.
 */
void bind_tile_texture(Tiles_Layer* tiles_layer);

/*! @brief Updates the pixels at the given points with the given value.
 *
 *  @param[in] tiles_layer The tiles layer to update.
 *  @param[in] x X offset of the pixel to update.
 *  @param[in] y Y offset of the pixel to update.
 *  @param[in] value The value used to update with.
 */
void update_tiles_layer_pixels(
    Tiles_Layer* tiles_layer,
    Point* points,
    Uint16 points_count,
    vec4 value
);

void update_tiles_layer_pixels_low(
    Tiles_Layer* tiles_layer,
    Point* points,
    Uint16 points_count,
    vec2 value
);

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
