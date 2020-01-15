#pragma once

#include "Game_Data/Property_Data/property_data.h"

/*! @brief Holds the data for one property type (city/base/etc).
 */
typedef struct Property_Type_Data {

    // How many army variations exist for this property type.
    Uint8 army_variation_count;

    // The frames corresponding to this property type's different variations.
    Frame* frames[ARMY_TYPE_COUNT];

} Property_Type_Data;

struct Property_Tiles_Data
{

    // All properties' source data.
    // Structure goes: Weather variation -> Property type -> Army variation
    Property_Type_Data* src[PROPERTY_WEATHER_COUNT][PROPERTY_TYPE_COUNT];

    // Currently active weather variation properties source data.
    Property_Type_Data* active_src[PROPERTY_TYPE_COUNT];

};
