#include <glad/glad.h>
#include <GLFW/glfw3.h>

void read_texture_data(GLuint texture, void* buffer, int width, int height)
{
    #ifdef __EMSCRIPTEN__
    GLuint FBO;

    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDeleteFramebuffers(1, &FBO);

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
