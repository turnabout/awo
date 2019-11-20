#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cJSON.h>

#include "Game/Data/Unit/enums.h"
#include "Game/Data/Tile/enums.h"
#include "Game/Data/Enums/weather.h"
#include "Game/Data/Enums/army_type.h"

/*! Texture containing every row of palette data that can be used by the game.
 *  Structure:
 *   0: Units: OS
 *   1: Units: OS (Done)
 *   2: Units: BM
 *   3: Units: BM (Done)
 *   4: Units: GE
 *   5: Units: GE (Done)
 *   6: Units: YC
 *   7: Units: YC (Done)
 *   8: Units: BH
 *   9: Units: BH (Done)
 *  10: Clear (Fog)
 *  11: Clear
 *  12: Clear (Fog)
 *  13: Snow
 *  14: Snow (Fog)
 *  15: Rain
 *  16: Rain (Fog)
 *  17: Properties: OS
 *  18: Properties: OS (Fog)
 *  19: Properties: BM
 *  20: Properties: BM (Fog)
 *  21: Properties: GE
 *  22: Properties: GE (Fog)
 *  23: Properties: YC
 *  24: Properties: YC (Fog)
 *  25: Properties: BH
 *  26: Properties: BH (Fog)
 *  27: Properties: Neutral
 *  28: Properties: Neutral (Fog)
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
GLfloat get_unit_palette_index(Army_Type unit_variation, GLboolean done);

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
GLfloat get_property_palette_index(Army_Type unit_variation);

/*! @brief Gets the integer palette index for a unit of the given variation.
 *
 *  @param[in] unit_variation The unit variation.
 *  @param[in] done Whether to get the "done" version of the unit palette.
 *  @return The integer index of the palette corresponding to the unit variation.
 */
GLint get_unit_palette_index_i(Army_Type unit_variation, GLboolean done);

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
GLint get_property_palette_index_i(Army_Type unit_variation);

/*! @brief Gets the integer palette index for the fog property palette row.
 *
 *  @return The integer index of the fog property palette.
 */
GLint get_raw_fog_property_palette_index_i();