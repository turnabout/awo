#include "GL_Helpers/gl_helpers.h"

void create_projection_matrix(int window_width, int window_height, mat4 projection)
{
    glm_ortho(0.0f, (float)window_width, (float)window_height, 0.0f, -1.0f, 1.0f, projection);
}