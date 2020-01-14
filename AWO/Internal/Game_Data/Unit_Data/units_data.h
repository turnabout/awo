#pragma once

#include <cJSON.h>
#include <cglm/types.h>

#include "Game_Data/Headers/army_types.h"
#include "Game_Data/Animation/animation.h"
#include "Headers/unit_types.h"

/*! @brief Holds all of the game's data for units.
 */
typedef struct Units_Data Units_Data;

// Creates units data object from JSON.
Units_Data* create_units_data(cJSON* units_data_JSON, int ss_width, int ss_height);

/*! @brief Gets the animation for a unit type and variation.
 *
 *  @param[in] units_data The units data module.
 *  @param[in] type The type of the unit.
 *  @param[in] variation The variation of the unit.
 *  @param[in] animation The unit animation to get.
 */
Animation* get_unit_animation(
    Units_Data* units_data,
    Unit_Type type,
    Army_Type variation,
    Unit_Anim animation
);

// Frees all memory occupied by units data.
void free_units_data(Units_Data* units_data);

#ifdef _DEBUG
// Prints the contents from units data.
void print_units_data(Units_Data* units_data);
#endif
