#pragma once

#include "cJSON.h"

/**
 *  \brief Holds all of the game's visuals data for units.
 */
typedef struct Units_Data Units_Data;

/**
 *  \brief Create units data object from JSON.
 *
 *  \param units_visuals_JSON The cJSON object containing units' JSON.
 */
Units_Data* UD_create_from_JSON(const cJSON* ud_JSON);

/**
 *  \brief Print contents of units data.
 *
 *  \param ud The Units_Data object to print.
 */
void UD_print(Units_Data* ud)
