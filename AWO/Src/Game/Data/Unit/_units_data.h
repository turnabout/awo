#pragma once

#include "Game/Data/Unit/units_data.h"
#include "types.h"

/*! @brief Animation data for a unit type/variation.
 */
typedef struct Unit_Animation_Data {
    Animation* animations[UNIT_ANIM_COUNT];
} Unit_Animation_Data;

/*! @brief A unit type's data.
 */
typedef struct Unit_Type_Data
{
    Uint8 variations_count;           // Amount of existing army variations on this unit type
    Unit_Animation_Data** variations; // Animation data for every variation of this unit type
} Unit_Type_Data;

/*! @brief All data for units.
 */
struct Units_Data
{
    Unit_Type_Data* src[UNIT_TYPE_COUNT];
};

void free_unit_type_data(Unit_Type_Data* type_data);
