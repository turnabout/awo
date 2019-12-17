#pragma once

#include <cJSON.h>

#include "Game/Data/CO/enums.h"

/*! @brief Holds all of the game's data for COs.
 */
typedef struct CO_Data CO_Data;

/*! @brief Creates the CO data object, containing data for all COs.
 *
 *  @param[in] CO_JSON The JSON describing the CO data.
 *  @param[in] ss_width The tiles_width of the game's sprite sheet.
 *  @param[in] ss_height The tiles_height of the game's sprite sheet.
 *  @return The generated CO data object.
 */
CO_Data* create_CO_data(cJSON* CO_JSON, int ss_width, int ss_height);

/*! @brief Frees the memory occupeid by the CO data object.
 *
 *  @param[in] CO_data The CO data object to free.
 */
void free_CO_data(CO_Data* CO_data);
