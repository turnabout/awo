#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/types.h>

#include "types.h"

typedef struct Render_Grid Render_Grid;

/*! @brief Creates a render grid.
 *
 *  @param[in] grid_width
 *  @param[in] grid_height
 *  @param[in] y_offset Amount of pixels used to offset the render grid vertically.
 *  @return The created render grid.
 */
Render_Grid* create_render_grid(GLuint grid_width, GLuint grid_height, GLuint y_offset);

/*! @brief Renders the given render grid.
 *
 *  @param[in] render_grid The render grid.
 */
void render_r_grid(Render_Grid* render_grid);

/*! @brief Updates the pixel data of the given render grid.
 *
 *  @param[in] render_grid The render grid to update.
 *  @param[in] points_array Array of points to update with the new value.
 *  @param[in] points_count Amount of points in the points array.
 *  @param[in] value The value to update the pixels with.
 */
void update_render_grid_pixels(
    Render_Grid* render_grid,
    Point* points_array,
    Uint16 points_count,
    vec4 value
);

/*! @brief Updates the low section of pixel data of the given render grid.
 *
 * Takes two values as an argument and applies it to the first two values of the pixels pointed at
 * by the points argument.
 *
 *  @param[in] render_grid The render grid to update.
 *  @param[in] points_array Array of points to update with the new value.
 *  @param[in] points_count Amount of points in the points array.
 *  @param[in] value The value to update the pixels with.
 */
void update_render_grid_pixels_low(
    Render_Grid* render_grid,
    Point* points,
    Uint16 points_count,
    vec2 value
);

/*! @brief Fill pixels' values in the render grid's texture.
 *
 *  @param[in] render_grid The render grid to update.
 *  @param[in] value The value used to update with.
 */
void fill_render_grid_pixels(Render_Grid* render_grid, vec4 value);

/*! @brief Frees memory used by the render grid.
 *
 *  @param[in] render_grid The render grid.
 */
void free_render_grid(Render_Grid* render_grid);
