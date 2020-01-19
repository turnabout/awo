#pragma once

#include "GL_Helpers/gl_helpers.h"
#include "Render_Grid/render_grid.h"

struct Render_Grid {

    // The render grid's pixel data.
    vec4* pixel_data;

    // The texture used by this grid to render.
    GLuint grid_texture;

    // VAO used to render this render grid.
    GLuint VAO;

    // Dimensions of the render grid.
    Uint8 width, height;

    // Whether the tiles layer's pixel data was changed since the last render.
    Bool dirty;
};

/*! @brief Get the VAO used by render grids.
 *
 *  @param[in] width Width taken up by the render grid's texture.
 *  @param[in] height Height taken up by the render grid's texture.
 *  @param[in] y_offset Amount of pixels used to offset the render grid vertically.
 *  @param[in] tiles_shader The tiles shader program.
 *  @return The tiles layers VAO.
 */
GLuint get_render_grid_VAO(
    GLuint width,
    GLuint height,
    GLuint vertical_offset,
    GLuint tiles_shader
);
