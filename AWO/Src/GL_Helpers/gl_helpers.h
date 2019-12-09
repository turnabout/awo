#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Creates a shader_program program, using the given paths to the vertex and fragment shaders.
// Returns the shader_program program ID or 0 if unsuccessful.
GLuint create_shader_program(const char* vertex_shader_path, const char* fragment_shader_path);

/*! @brief Creates a texture object from an image loaded at the given path.
 *
 *  @param[in] texture_path The full path to the texture.
 *  @param[out] texture_width The tiles_width of the loaded texture.
 *  @param[out] texture_height The tiles_height of the loaded texture.
 *  @return The texture object ID or 0 if an error occurred.
 */
GLuint create_texture_object(const char* texture_path, int* texture_width, int* texture_height);

/*! @brief Reads the data from the given texture.
 *
 *  @param[in] texture Texture to read the data from.
 *  @param[out] buffer Buffer the data is read into.
 *  @param[in] width Width of the texture.
 *  @param[in] height Height of the texture.
 */
void read_texture_data(GLuint texture, void* buffer, int width, int height);