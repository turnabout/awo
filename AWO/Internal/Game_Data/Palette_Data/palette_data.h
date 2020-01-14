#pragma once

typedef struct Palette_Data Palette_Data;

typedef GLubyte Palette_Texture_Row[PALETTE_TEX_WIDTH][4];

// Counts of every different types of palettes
#define UNIT_PALETTE_COUNT (ARMY_TYPE_COUNT) * (2) // 2 of each unit variation (normal / done)
#define TILE_PALETTE_COUNT (WEATHER_COUNT)  * (2)  // 2 of each tile variation (normal / foggy)
#define PROP_PALETTE_COUNT ARMY_TYPE_COUNT + 2     // + 2 is neutral & fogged