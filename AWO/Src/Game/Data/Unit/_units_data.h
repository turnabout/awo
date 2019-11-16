#pragma once

#include "Game/Data/Unit/units_data.h"
#include "types.h"

typedef struct Unit_Type_Data
{
    Uint8 variations_count;  // Amount of variations used by this unit type
    Animation*** variations; // Animation data for every variation of this unit type
} Unit_Type_Data;

struct Units_Data
{
    Unit_Type_Data* src[UNIT_TYPE_COUNT];
};
