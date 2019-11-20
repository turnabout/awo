#pragma once

#include "Game/Data/Unit/enums.h"
#include "Game/Player/CO/enums.h"

/*! @brief Commanding Officer.
 *
 * The characters used by players during gameplay. Determine things like units' special abilities,
 * attributes, the usable CO power and the version of certain visuals used during gameplay.
 */
typedef struct CO {

    // The CO's name.
    char name[16];

    // Army the CO belongs to. Determines which visuals are used for certain properties & units.
    Unit_Variation army;

} CO;