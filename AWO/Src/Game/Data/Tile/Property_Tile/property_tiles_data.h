#pragma once

#include <cJSON.h>

#include "Game/Data/Unit/enums.h"
#include "Game/Data/Tile/Property_Tile/enums.h"
#include "Game/Data/Enums/weather.h"
#include "Game/Data/Enums/army_type.h"

typedef struct Tiles_Data Tiles_Data;

/*! @brief Holds the data for one property type.
 */
typedef struct Property_Type_Data Property_Type_Data;

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

/*! @brief Retrieves the property type data object of a property type.
 *
 *  @param[in] tiles_data The tiles data object.
 *  @param[in] weather_variation The weather variation of the property type data to get.
 *  @param[in] property_type The property type of the frame to get.
 *  @return The property type data object.
 */
Property_Type_Data* get_property_type_data(
    Tiles_Data* tiles_data,
    Weather weather_variation,
    Property_Type property_type
);

/*! @brief Retrieves a frame in the given property type data corresponding to the given variations.
 *
 *  @param[in] property_type_data The property type data object of the frame to get.
 *  @param[in] army_variation The army variation of the frame to get.
 *  @return The retrieved frame with the given variations.
 */
Frame* get_property_type_frame(Property_Type_Data* property_type_data, Army_Type army_variation);

/*! @brief Frees the memory occupied by the properties data object.
 *
 *  @param[in] tiles_data The tiles data object.
 */
void free_properties_data(Tiles_Data* tiles_data);
