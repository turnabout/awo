#pragma once

#include "cJSON.h"
#include "tiles_enums.h"

/**
 *  \brief Holds all of the game's visuals data for tiles.
 */
typedef struct Tiles_Data Tiles_Data;

/**
 *  \brief Create tiles data object from JSON.
 *
 *  \param units_visuals_JSON The cJSON object containing tiles' JSON.
 *
 *  \return Returns the initialized tiles' data.
 */
Tiles_Data* TD_create_from_JSON(cJSON* tiles_visuals_JSON);

#ifdef _DEBUG
/**
 *  \brief Print contents from tiles data.
 *
 *  \param ud The Tiles_Data object to print.
 * 
 *  \param which Which part of the tiles' data to print.
 */
void TD_print(Tiles_Data* td);
#endif

// TODO: still need?
/**
 *  \brief Gets a tile's data.
 *
 *  \param type The tile type.
 *
 *  \return Returns the tile data associated with the given tile type.
 */
// Tile_Data* access_tile(tile_type type);

// TODO: still need?
/**
 *  \brief Gets a tile's variation's data.
 *
 *  \param type The tile type.
 *
 *  \param var The tile variation.
 *
 *  \return Returns the tile variation data associated with the given tile type and tile variation.
 *          Returns NULL if given variation was not found on the tile type.
 */
// Tile_Var_Data* access_tile_var(tile_type type, tile_var var);
