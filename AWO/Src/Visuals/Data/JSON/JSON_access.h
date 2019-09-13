#pragma once
#include "cJSON.h"

/**
 *  \brief Loads the game's visuals JSON file contents into a cJSON struct.
 *
 *  \param cJSON Pointer to a cJSON struct pointer, holding the result.
 *
 *  \return Returns ERR if an error occurred, or OK.
 *
 *  \sa load_visuals_JSON()
 */
int load_visuals_JSON(const cJSON **visuals_JSON);
