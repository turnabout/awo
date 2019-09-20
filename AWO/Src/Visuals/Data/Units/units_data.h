#pragma once

#include "cJSON.h"
#include "units_enums.h"

/**
 *  \brief Holds all of the game's visuals data for units.
 */
typedef struct Units_Data Units_Data;

/**
 *  \brief Create units data object from JSON.
 *
 *  \param units_visuals_JSON The cJSON object containing units' JSON.
 *
 *  \return Returns the initialized units' data.
 */
Units_Data* UD_create_from_JSON(const cJSON* ud_JSON);

#ifdef _DEBUG

typedef enum {
    UD_SRC,
    UD_DST,
} UD_print_arg;

/**
 *  \brief Print contents from units data.
 *
 *  \param ud The Units_Data object to print.
 *
 *  \param which Which part of the units' data to print.
 */
void UD_print(Units_Data* ud, UD_print_arg which);
#endif
