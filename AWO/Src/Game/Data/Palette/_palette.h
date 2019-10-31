#pragma once

#define PALETTE_TEX_WIDTH  256
#define PALETTE_TEX_HEIGHT   3

#include "Game/Data/Palette/palette.h"

/*! @brief Initializes Normalized Device Coordinate palette indexes.
 *
 *  The NDC palette indexes are used by game entities to index into the palette texture when 
 *  rendering. This initializes those values based on the amount of generated palette rows in
 *  create_palette_texture, and makes it so get_palette_index functions can return proper palette
 *  texture Normalized Device Coordinates.
 *  
 *  @param[in] palette_count How many palettes were generated in create_palette_texture.
 */
void init_palette_NDC_indexes(int palette_count);