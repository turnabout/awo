#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Utilities/utilities.h"

/*! @brief Module used to read sections of a texture loaded into GL.
 */
typedef struct Texture_Reader Texture_Reader;

/*! @brief Creates a texture reader.
 *
 *  @param[in] texture The texture this texture reader should read from.
 *  @return The created texture reader.
 */
Texture_Reader* create_texture_reader(GLuint texture, int texture_w, int texture_h);

/*! @brief Reads data at coordinates from the texture loaded in the texture reader.
 *
 *  @param[in] reader The texture reader to read from.
 *  @param[in] x The source X coordinate of the texture to read from.
 *  @param[in] y The source Y coordinate of the texture to read from.
 *  @param[in] w The source width of the data to read.
 *  @param[in] h The source height of the data to read.
 *  @return Buffer filled with the texture pixel data.
 */
Uint8* read_texture_src_data(Texture_Reader* reader, int x, int y, int w, int h);

/*! @brief Frees the texture reader.
 *
 *  @param[in] texture The texture reader to free.
 */
void free_texture_reader(Texture_Reader* texture_reader);