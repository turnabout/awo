#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/*! @brief Module used to read sections of a texture loaded into GL.
 */
typedef struct Texture_Reader Texture_Reader;

/*! @brief Creates a texture reader.
 *
 *  @param[in] texture The texture this texture reader should read from.
 *  @return The created texture reader.
 */
Texture_Reader* create_texture_reader(GLuint texture, int texture_w, int texture_h);

void read_texture_src_data(Texture_Reader* texture_reader, int x, int y, int w, int h);

/*! @brief Frees the texture reader.
 *
 *  @param[in] texture The texture reader to free.
 */
void free_texture_reader(Texture_Reader* texture_reader);