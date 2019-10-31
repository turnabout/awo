#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cJSON.h>

#include "Game/Data/Unit/enums.h"
#include "Game/Data/Tile/enums.h"

/*! @brief Creates the main palette texture used to color swap sprites.
 *
 *  @param[in] data_JSON The entire JSON data file.
 *  @return ID of the generated texture object.
 */
GLuint create_palette_texture(cJSON* data_JSON);

/*! @brief Gets the palette index for a unit of the given variation.
 *
 *  @param[in] unit_variation The unit variation.
 *  @return The index of the palette corresponding to the unit variation.
 */
GLfloat get_unit_palette_index(Unit_Variation unit_variation);

/*! @brief Gets the palette index for a tile of the given weather and fog status.
 *
 *  @param[in] weather The weather.
 *  @param[in] fog Whether to get the "fog" version of the weather palette.
 *  @return The index of the palette corresponding to the weather/fog combination.
 */
GLfloat get_tile_palette_index(Weather weather, GLboolean fog);

/*! @brief Frees data allocated for NDC palette indexes.
 */
void free_palette_NDC_indexes();