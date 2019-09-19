#pragma once

#include "C_Hashmap/hashmap.h"
#include "../general_data_access.h"
#include "../Palettes/palette_tree.h"
#include "tiles_enums.h"

/**
 * \brief Represents a tile's visual data.
 */
typedef struct
{
    map_t vars;          // Map holding every variation's animation
    int vars_amount;     // Amount of variations this tile has
    tile_var* vars_list; // List of every variation this tile has
    int sub_clock_data;  // TODO
} Tile_Data;

/**
 * \brief Represents all visual data used by tiles.
 */
typedef struct
{
    Tile_Data* src[TILE_TYPE_AMOUNT];
    SS_Meta_Data* ss_meta_data;
} Tiles_Data;

/**
 *  \brief Gets a tile's variation's animation.
 *
 *  \param type The tile type.
 *
 *  \param var The tile variation.
 *
 *  \return Returns the animation associated with the given tile type and tile variation.
 *          Returns NULL if given variation was not found on the tile type.
 */
Animation* access_tile_var_anim(tile_type type, tile_var var);