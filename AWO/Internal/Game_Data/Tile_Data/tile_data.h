#pragma once

#include <cJSON.h>

#include "Game_Data/Tile_Data/Tile_Type_Data/tile_type_data.h"

#include "Headers/macros.h"

/*! @brief Holds all of the game's data for regular tiles.
 */
typedef struct Tiles_Data
{

    // Data for every tile type.
    Tile_Type_Data* src[NEUTRAL_TILE_TYPE_COUNT];

} Tiles_Data;

/*! @brief Creates the tile data module.
 *
 *  @param[in] tiles_data_JSON The JSON describing tile data.
 *  @param[in] ss_width The width of the game's sprite sheet.
 *  @param[in] ss_height The height of the game's sprite sheet.
 *  @return The generated tile data object.
 */
Tiles_Data* create_tile_data(cJSON* tiles_data_JSON, int ss_width, int ss_height);

/*! @brief Frees all memory occupied by the tile data module.
 *
 *  @param[in] tiles_data The tiles data object.
 */
void free_tile_data(Tiles_Data* tiles_data);

#ifdef _DEBUG
/*! @brief Prints all contents stored in tiles data.
 *
 *  @param[in] tiles_data The tiles data object.
 */
void print_tiles_data(Tiles_Data* tiles_data);
#endif
