#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cJSON.h>

#include "Game_Data/Headers/army_types.h"
#include "Game_Data/Headers/weather.h"
#include "Game_Data/Unit_Data/unit_data.h"

#define PALETTE_TEX_WIDTH  256
#define PALETTE_TEX_HEIGHT  32

// Counts of every different types of palettes
#define UNIT_PALETTE_COUNT (ARMY_TYPE_COUNT) * (2) // 2 of each unit variation (normal / done)
#define TILE_PALETTE_COUNT (WEATHER_COUNT)  * (2)  // 2 of each tile variation (normal / foggy)
#define PROP_PALETTE_COUNT ARMY_TYPE_COUNT + 2     // + 2 is neutral & fogged

/*! @brief Module containing all palette data that can be used by the game.
 *
 *  Contains all palette data usable by the game.
 *  The palette is stored both in an actual texture and in an allocated buffer.
 */
typedef struct Palette_Data Palette_Data;

/*! @brief A row of palette data.
 */
typedef GLubyte Palette_Data_Row[PALETTE_TEX_WIDTH][4];

/*! @brief Creates the palette data module.
 *
 *  @param[in] palette_JSON The palette data JSON object.
 *  @return The created palette data module.
 */
Palette_Data* create_palette_data(cJSON* palette_JSON);

/*! @brief Gets reference to a unit palette data row.
 *
 *  @param[in] palette_data The palette data module.
 *  @param[in] army The army type of the unit palette.
 *  @param[in] done The "done" status of the unit palette.
 *  @return The unit palette data row corresponding to the given army type & done status.
 */
Palette_Data_Row* get_palette_data_unit_row(Palette_Data* palette_data, Army_Type army, Bool done);

/*! @brief Gets reference to a tile palette data row.
 *
 *  @param[in] palette_data The palette data module.
 *  @param[in] weather The weather of the tile palette.
 *  @param[in] fog The "fog" status of the tile palette.
 *  @return The tile palette data row corresponding to the given weather & fog status.
 */
Palette_Data_Row* get_palette_data_tile_row(Palette_Data* palette_data, Weather weather, Bool fog);

/*! @brief Gets reference to a property palette data row.
 *
 *  @param[in] palette_data The palette data module.
 *  @param[in] army The army type of the property palette.
 *  @return The property palette data row corresponding to the given army type.
 */
Palette_Data_Row* get_palette_data_property_row(Palette_Data* palette_data, Army_Type army);

/*! @brief Gets reference to the fog property palette data row.
 *
 *  @param[in] palette_data The palette data module.
 *  @return The fog property palette data row.
 */
Palette_Data_Row* get_palette_data_fog_property_row(Palette_Data* palette_data);

/*! @brief Gets the NDC (Normalized Device Coordinate) palette index corresponding to palette row.
 *
 * @param palette_row Which palette row to get the NDC index value for.
 * @return The NDC palette index.
 */
GLfloat get_palette_NDC_index(GLuint palette_row);

/*! @brief Frees a created palette data module.
 *
 *  @param[in] palette_data The palette data module to free.
 */
void free_palette_data(Palette_Data* palette_data);