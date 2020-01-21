#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include "Include/types.h"

/*! @brief Creates a shader program.
 *
 *  @param[in] vertex_shader_path Full path to the vertex shader used to make up the program.
 *  @param[in] fragment_shader_path Full path to the fragment shader used to make up the program.
 *  @return The shader program ID or 0 if unsuccessful.
 */
GLuint create_shader_program(const char* vertex_shader_path, const char* fragment_shader_path);

/*! @brief Creates a texture object from the given image data buffer.
 *
 *  @param[in] image_buffer The image data buffer representing the image.
 *  @param[in] width The width of the image represented by the buffer.
 *  @param[in] height The height of the image represented by the buffer.
 *  @param[in] channels_amount The amount of channels the image data buffer contains. Only 3/4 are
 *  supported internally at the moment.
 *  @return The texture object ID or 0 if an error occurred.
 */
GLuint create_texture_object(Uint8* image_buffer, int width, int height, int channels_amount);

/*! @brief Creates an empty texture object.
 *
 *  @param[out] width The width given to the empty texture.
 *  @param[out] height The height given to the empty texture.
 *  @return The texture object ID or 0 if an error occurred.
 */
GLuint create_empty_texture_object(int width, int height);

/*! @brief Deletes the given texture object.
 *
 *  @param[int] texture The texture to delete.
 */
void delete_texture(GLuint texture);

/*! @brief Reads the data from the given texture.
 *
 *  @param[in] texture Texture to read the data from.
 *  @param[out] buffer Buffer the data is read into.
 *  @param[in] width Width of the texture.
 *  @param[in] height Height of the texture.
 */
void read_texture_data(GLuint texture, void* buffer, int width, int height);

/*! @brief Creates a projection matrix using the given window dimensions.
 *
 *  @param[in] window_width Width of the window.
 *  @param[in] window_height Height of the window.
 *  @param[out] projection Destination of the generated projection matrix.
 */
void create_projection_matrix(int window_width, int window_height, mat4 projection);