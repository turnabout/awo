#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cJSON.h>

#include "types.h"
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
 *  10: Clear
 *  11: Clear (Fog)
 *  12: Snow
 *  13: Snow (Fog)
 *  14: Rain
 *  15: Rain (Fog)
 *  16: Properties: OS
 *  17: Properties: BM
 *  18: Properties: GE
 *  19: Properties: YC
 *  20: Properties: BH
 *  21: Properties: Neutral
 *  22: Properties: (Fog)
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
GLfloat get_raw_unit_palette_index(Army_Type unit_variation, Bool done);

/*! @brief Gets the NDC palette index for a tile of the given weather and fog status.
 *
 *  @param[in] weather The weather.
 *  @param[in] fog Whether to get the "fog" version of the weather palette.
 *  @return The index of the palette corresponding to the weather/fog combination.
 */
GLfloat get_raw_tile_palette_index(Weather weather, Bool fog);

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
GLfloat get_raw_property_palette_index(Army_Type unit_variation);

/*! @brief Gets the integer palette index for a unit of the given variation.
 *
 *  @param[in] unit_variation The unit variation.
 *  @param[in] done Whether to get the "done" version of the unit palette.
 *  @return The integer index of the palette corresponding to the unit variation.
 */
GLuint get_raw_unit_palette_index_i(Army_Type unit_variation, Bool done);

/*! @brief Gets the integer palette index for a tile of the given weather and fog status.
 *
 *  @param[in] weather The weather.
 *  @param[in] fog Whether to get the "fog" version of the weather palette.
 *  @return The integer index of the palette corresponding to the weather/fog combination.
 */
GLuint get_raw_tile_palette_index_i(Weather weather, Bool fog);

/*! @brief Gets the integer palette index for a property of the given unit variation.
 *
 *  @param[in] unit_variation The unit variation.
 *  @return The integer index of the palette corresponding to the property of the given variation.
 */
GLuint get_raw_property_palette_index_i(Army_Type unit_variation);

/*! @brief Gets the integer palette index for the fog property palette row.
 *
 *  @return The integer index of the fog property palette.
 */
GLuint get_raw_fog_property_palette_index_i();