#pragma once

#include "Game_Data/Headers/army_types.h"
#include "Game_Data/Unit_Data/unit_data.h"
#include "Game_Data/CO_Data/CO_data.h"

/*! @brief Commanding Officer.
 *
 * The characters used by players during gameplay. Determine things like units' special abilities,
 * attributes, the usable CO power and the version of certain visuals used during gameplay.
 */
typedef struct CO {

    // The CO's name.
    const char* name;

    // Army the CO belongs to. Determines which visuals are used for certain properties & units.
    Army_Type army;

} CO;

/*! @brief Creates a CO usable by a player.
 *
 *  @param[in] co_type The type of the CO.
 *  @return The created CO.
 */
CO* create_CO(CO_Type co_type);

/*! @brief Frees the memory allocated by the given CO.
 *
 *  @param[in] co The CO to free.
 */
void free_CO(CO* co);