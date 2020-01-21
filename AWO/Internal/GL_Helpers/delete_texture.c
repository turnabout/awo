#include "GL_Helpers/gl_helpers.h"

void delete_texture(GLuint texture)
{
    if (texture != 0) {
        glDeleteTextures(1, &texture);
    }
}