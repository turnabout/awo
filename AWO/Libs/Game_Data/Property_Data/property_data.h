#pragma once

#include <cJSON.h>

#include "Headers/macros.h"
#include "AWO/game_data.h"
#include "Game_Data/Frame/frame.h"

/*! @brief Creates the properties data object.
 *
 *  @param[in] properties_data_JSON The JSON describing the properties' data.
 *  @param[in] ss_width The tiles_width of the game's sprite sheet.
 *  @param[in] ss_height The tiles_height of the game's sprite sheet.
 *  @return The generated properties data object.
 */
Property_Data* create_property_tiles_data(
    cJSON* properties_data_JSON,
    int ss_width,
    int ss_height
);

/*! @brief Updates the current active property weather variation for tiles data.
 *
 * This will update the weather variation currently used by all properties in the game.
 *
 *  @param[in] property_data The property data module.
 *  @param[in] weather_variation The weather variation to update to.
 */
void update_tiles_data_active_property_weather_var(
    Property_Data* property_data, 
    Weather weather
);

/*! @brief Retrieves a frame for a property of the given type and army variation.
 *
 *  @param[in] property_data The property data object.
 *  @param[in] property_type The property type of the frame to get.
 *  @param[in] army_variation The army variation of the frame to get.
 *  @return Pointer to the retrieved frame pointer.
 */
Frame** get_property_type_frame(
    Property_Data* property_data,
    Property_Type property_type,
    Army_Type army_variation
);

/*! @brief Frees the memory occupied by the properties data object.
 *
 *  @param[in] tiles_data The tiles data object.
 */
void free_properties_data(Property_Data* property_data);
