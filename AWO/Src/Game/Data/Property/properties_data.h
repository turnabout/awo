#pragma once

#include <cJSON.h>

#include "Game/Data/Property/enums.h"

/*! @brief Holds all of the game's data for properties.
 */
typedef struct Properties_Data Properties_Data;

/*! @brief Creates the properties data object.
 *
 *  @param[in] properties_data_JSON The JSON describing the properties' data.
 *  @param[in] ss_width The tiles_width of the game's sprite sheet.
 *  @param[in] ss_height The tiles_height of the game's sprite sheet.
 *  @return The generated properties data object.
 */
Properties_Data* create_properties_data(cJSON* properties_data_JSON, int ss_width, int ss_height);
