#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cJSON.h>

/*! @brief Creates the main palette texture used to color swap sprites.
 *
 *  @param[in] data_JSON The entire JSON data file.
 *  @return ID of the generated texture object.
 */
GLuint create_palette_texture(cJSON* data_JSON);