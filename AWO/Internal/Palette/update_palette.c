#include <stdlib.h>

#include "Palette/_palette.h"

// TODO: take in a unit variation as an arg instead of a palette index
void update_unit_palette_black_pixel(GLuint palette_index, GLubyte new_color)
{
    GLubyte new_color_array[4] = { new_color, new_color, new_color, 255 };

    glTexSubImage2D(
        GL_TEXTURE_2D,
        0,
        0,
        palette_index,
        1,
        1,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        &new_color_array
    );
}
