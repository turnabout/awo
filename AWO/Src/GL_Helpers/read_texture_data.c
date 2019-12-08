#include <glad/glad.h>
#include <GLFW/glfw3.h>

void read_texture_data(GLuint texture, void* buffer)
{
    #ifdef __EMSCRIPTEN__

    #else
    glBindTexture(GL_TEXTURE_2D, texture);

    glGetTexImage(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        buffer
    );
    #endif
}
