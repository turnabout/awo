#pragma once

#include "Game/Data/Animation/Frame/frame.h"
#include "Game/Data/Property/properties_data.h"
#include "Game/Data/Tile/enums.h"
#include "Game/Data/Enums/weather.h"
#include "Game/Data/Unit/enums.h"

typedef struct Property_Type_Data {

    // How many army variations per weather variation of this property type exist.
    Uint8 army_variation_count;

    // The frames corresponding to this property type's different variations.
    Frame** frames[PROPERTY_WEATHER_COUNT];

} Property_Type_Data;

struct Properties_Data
{
    // All properties' source data.
    // Structure goes: Property type -> Weather variation -> Army variation
    Property_Type_Data* src[PROPERTY_TYPE_COUNT];
};
