#pragma once

#include "Game/Data/Animation/Frame/frame.h"
#include "Game/Data/Tile/Property_Tile/property_tiles_data.h"
#include "Game/Data/Tile/enums.h"
#include "Game/Data/Enums/weather.h"
#include "Game/Data/Unit/enums.h"

/*! @brief Holds the data for one property type (city/base/etc).
 */
typedef struct Property_Type_Data {

    // How many army variations per weather variation of this property type exist.
    Uint8 army_variation_count;

    // The frames corresponding to this property type's different variations.
    Frame** frames;

} Property_Type_Data;

struct Property_Tiles_Data
{
    // All properties' source data.
    // Structure goes: Weather variation -> Property type -> Army variation
    Property_Type_Data* src[PROPERTY_WEATHER_COUNT][PROPERTY_TYPE_COUNT];

    // Currently used weather variation properties' source data.
    // Points to either src[Clear][type] or src[Snow][type]
    Property_Type_Data** active_src;
};
