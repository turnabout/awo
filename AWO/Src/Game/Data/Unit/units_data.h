#pragma once

#include <cJSON.h>
#include <cglm/types.h>

#include "Game/Data/Enums/army_type.h"
#include "Game/Data/Unit/enums.h"
#include "Game/Data/Animation/animation.h"

// Holds all of the game's visuals data for units.
typedef struct Units_Data Units_Data;

// Creates units data object from JSON.
Units_Data* create_units_data(const cJSON* units_data_JSON, int ss_width, int ss_height);

// Gets the source animations data for a unit type & variation.
Animation** get_unit_animations(Units_Data* units_data, Unit_Type type, Army_Type variation);

// Frees all memory occupied by units data.
void free_units_data(Units_Data* units_data);

#ifdef _DEBUG
// Prints the contents from units data.
void print_units_data(Units_Data* units_data);
#endif
