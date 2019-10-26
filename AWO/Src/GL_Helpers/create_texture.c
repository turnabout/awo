#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLuint create_texture_object(const char* path)
{
    // Tell stb_image to flip the y-axis during image loading.
    // This is because OpenGL expects the 0.0 coordinate on the y-axis to be the bottom side of the
    // image, but images usually have 0.0 at the top of the y-axis.
    stbi_set_flip_vertically_on_load(1);

    // Load texture image
    GLint width, height, channels_amount;
    unsigned char* data = stbi_load(path, &width, &height, &channels_amount, 0);

    if (!data) {
        printf("Failed to load texture image at %s\n", path);
        return 0;
    }

    // Create texture object
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Generate texture
    GLenum format = (channels_amount == 4)
        ? GL_RGBA
        : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    // Free the image memory
    stbi_image_free(data);

    return texture;
}
