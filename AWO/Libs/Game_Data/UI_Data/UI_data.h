#pragma once

#include <cjson/cJSON.h>

#include "AWO/game_data.h"
#include "Game_Data/Animation/animation.h"
#include "Headers/UI_elements.h"

/*! @brief Creates the UI data object, containing frame data for all UI elements.
 *
 *  @param[in] UI_JSON The JSON describing the UI data.
 *  @param[in] ss_width The tiles_width of the game's sprite sheet.
 *  @param[in] ss_height The tiles_height of the game's sprite sheet.
 *  @return The generated UI data object.
 */
UI_Data* create_UI_data(cJSON* UI_JSON, int ss_width, int ss_height);

/*! @brief Gets the animation frames for a UI element.
 *
 *  @param[in] UI_data The UI data object.
 *  @param[in] element The element for which to get the animation frames.
 *  @return The animation object corresponding to the given element. NULL if it doesn't exist.
 */
Animation* get_UI_element_frames(UI_Data* UI_data, UI_Element_Type element);

/*! @brief Frees the memory occupeid by the UI data object.
 *
 *  @param[in] UI_data The UI data object to free.
 */
void free_UI_data(UI_Data* UI_data);
