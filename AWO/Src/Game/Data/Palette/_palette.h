#pragma once

#define PALETTE_TEX_WIDTH  256
#define PALETTE_TEX_HEIGHT  32

// Counts of every different types of palettes
#define UNIT_PALETTE_COUNT (UNIT_VAR_COUNT) * (2) // 2 of each unit variation (normal / done)
#define TILE_PALETTE_COUNT (WEATHER_COUNT)  * (2) // 2 of each tile variation (normal / foggy)
#define PROP_PALETTE_COUNT UNIT_VAR_COUNT + 2     // + 2 is neutral & fogged

// Index of the texture rows reserved for the currently active tile palette
#define ACTIVE_TILE_PALETTE_INDEX     PROP_PALETTE_COUNT
#define ACTIVE_FOG_TILE_PALETTE_INDEX PROP_PALETTE_COUNT + 1
#define ACTIVE_TILE_PALETTE_COUNT     2

// Index of the texture rows reserved for the players
// #define PLAYERS_PALETTES_INDEX_START PROP_PALETTE_COUNT + ACTIVE_TILE_PALETTE_COUNT
// #define PLAYERS_PALETTE_COUNT PROP_PALETTE_COUNT

#include "Game/Data/Palette/raw_palette.h"
#include "Game/Data/Palette/game_palette.h"

typedef GLubyte Palette_Texture_Row[PALETTE_TEX_WIDTH][4];

/*! @brief Initializes Normalized Device Coordinate palette indexes.
 *
 *  The NDC palette indexes are used by game entities to index into the palette texture when 
 *  rendering. This initializes those values based on the amount of generated palette rows in
 *  create_palette_texture, and makes it so get_palette_index functions can return proper palette
 *  texture Normalized Device Coordinates.
 */
void init_palette_NDC_indexes();

void init_raw_palette_NDC_indexes();


/*! @brief Gets the NDC palette index at the given row.
 *
 * @param palette_row Which palette row to get the NDC index value of.
 * @return The Normalized Device Coordinate palette index.
 */
GLfloat get_palette_NDC_index(GLuint palette_row);