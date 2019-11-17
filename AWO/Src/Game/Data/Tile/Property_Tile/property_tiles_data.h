#pragma once

#include <cJSON.h>

#include "Game/Data/Unit/enums.h"
#include "Game/Data/Tile/Property_Tile/enums.h"
#include "Game/Data/Enums/weather.h"

/*! @brief Holds all of the game's data for properties.
 */
typedef struct Property_Tiles_Data Property_Tiles_Data;

/*! @brief Creates the properties data object.
 *
 *  @param[in] properties_data_JSON The JSON describing the properties' data.
 *  @param[in] ss_width The tiles_width of the game's sprite sheet.
 *  @param[in] ss_height The tiles_height of the game's sprite sheet.
 *  @return The generated properties data object.
 */
Property_Tiles_Data* create_property_tiles_data(
    cJSON* properties_data_JSON, 
    int ss_width, 
    int ss_height
);

/*! @brief Retrieves the frame corresponding to the given property info.
 *
 *  @param[in] properties_data The properties data object.
 *  @param[in] property_type The property type of the frame to get.
 *  @param[in] weather_variation The weather variation of the frame to get.
 *  @param[in] army_variation The army variation of the frame to get.
 *  @return The frame representing the property corresponding to the given arguments.
 */
Frame* get_property_frame(
    Property_Tiles_Data* properties_data, 
    Property_Type property_type, 
    Weather weather_variation, 
    Unit_Variation army_variation
);

/*! @brief Frees the memory occupied by the properties data object.
 *
 *  @param[in] properties_data The properties data object.
 */
void free_properties_data(Property_Tiles_Data* properties_data);
