#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cJSON.h>

#include "Game/Data/Unit/enums.h"
#include "Game/Data/Tile/enums.h"
#include "Game/Data/Enums/weather.h"

/*! @brief Texture containing every row of palette data that can be used by the game.
 *  Structure:
 *   0: Clear
 *   1: Clear (Fog)
 *   2: Snow
 *   3: Snow (Fog)
 *   4: Rain
 *   5: Rain (Fog)
 */

/*! @brief Creates the main palette texture used to color swap sprites.
 *
 *  @param[in] palette_JSON The palette data JSON object.
 *  @return The generated texture ID.
 */
GLuint create_raw_palette_texture(cJSON* palette_JSON);

/*! @brief Gets the NDC palette index for a unit of the given variation.
 *
 *  @param[in] unit_variation The unit variation.
 *  @param[in] done Whether to get the "done" version of the unit palette.
 *  @return The index of the palette corresponding to the unit variation.
 */
GLfloat get_unit_palette_index(Unit_Variation unit_variation, GLboolean done);

/*! @brief Gets the NDC palette index for a tile of the given weather and fog status.
 *
 *  @param[in] weather The weather.
 *  @param[in] fog Whether to get the "fog" version of the weather palette.
 *  @return The index of the palette corresponding to the weather/fog combination.
 */
GLfloat get_tile_palette_index(Weather weather, GLboolean fog);

/*! @brief Gets the currently active tile or fog tile palette.
 *
 *  @param[in] fog Whether to get the "fog" version of the weather palette.
 *  @return The index of the active tile or fog palette.
 */
GLfloat get_active_tile_palette_index(GLboolean fog);

/*! @brief Gets the NDC palette index for a property of the given unit variation.
 *
 *  @param[in] unit_variation The unit variation.
 *  @return The index of the palette corresponding to the property of the given variation.
 */
GLfloat get_property_palette_index(Unit_Variation unit_variation);

/*! @brief Gets the integer palette index for a unit of the given variation.
 *
 *  @param[in] unit_variation The unit variation.
 *  @param[in] done Whether to get the "done" version of the unit palette.
 *  @return The integer index of the palette corresponding to the unit variation.
 */
GLint get_unit_palette_index_i(Unit_Variation unit_variation, GLboolean done);

/*! @brief Gets the integer palette index for a tile of the given weather and fog status.
 *
 *  @param[in] weather The weather.
 *  @param[in] fog Whether to get the "fog" version of the weather palette.
 *  @return The integer index of the palette corresponding to the weather/fog combination.
 */
GLint get_tile_palette_index_i(Weather weather, GLboolean fog);

/*! @brief Gets the integer palette index for a property of the given unit variation.
 *
 *  @param[in] unit_variation The unit variation.
 *  @return The integer index of the palette corresponding to the property of the given variation.
 */
GLint get_property_palette_index_i(Unit_Variation unit_variation);

/*! @brief Updates the black pixel on the palette at the given index.
 *
 * Note: The palettes texture must be bound before calling this function.
 *
 *  @param[in] palette_index Index of the palette to update.
 *  @param[in] new_color Color to replace the current black pixel value with.
 */
void update_unit_palette_black_pixel(GLint palette_index, GLubyte new_color);

/*! @brief Updates the currently active tile palette.
 *
 * Note: The palettes texture must be bound before calling this function.
 *
 *  @param[in] weather The weather of the new active tile palette.
 */
void update_active_tile_palette(Weather weather);