#pragma once

#include <cJSON.h>

#include "Game/Data/UI/enums.h"

/*! @brief Holds all of the game's data for UI elements.
 */
typedef struct UI_Data UI_Data;

/*! @brief Creates the UI data object, containing frame data for all UI elements.
 *
 *  @param[in] UI_JSON The JSON describing the UI data.
 *  @param[in] ss_width The tiles_width of the game's sprite sheet.
 *  @param[in] ss_height The tiles_height of the game's sprite sheet.
 *  @return The generated UI data object.
 */
UI_Data* create_UI_data(cJSON* UI_JSON, int ss_width, int ss_height);

/*! @brief Frees the memory occupeid by the UI data object.
 *
 *  @param[in] UI_data The UI data object to free.
 */
void free_UI_data(UI_Data* UI_data);
