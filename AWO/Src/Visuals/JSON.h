#pragma once

/**
 *  \brief Loads the game's visuals JSON file into a cJSON struct, storing it 
 *         internally.
 *
 *  \return Returns ERR if an error occurred, or OK.
 *
 *  \sa load_visuals_JSON()
 */
int load_visuals_JSON();

void test_JSON();
