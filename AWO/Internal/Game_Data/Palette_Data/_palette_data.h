#pragma once

#include "Game_Data/Palette_Data/palette_data.h"

/*!
 *  Internal palette data structure:
 *   0: Units: OS
 *   1: Units: OS (Done)
 *   2: Units: BM
 *   3: Units: BM (Done)
 *   4: Units: GE
 *   5: Units: GE (Done)
 *   6: Units: YC
 *   7: Units: YC (Done)
 *   8: Units: BH
 *   9: Units: BH (Done)
 *  10: Clear
 *  11: Clear (Fog)
 *  12: Snow
 *  13: Snow (Fog)
 *  14: Rain
 *  15: Rain (Fog)
 *  16: Properties: OS
 *  17: Properties: BM
 *  18: Properties: GE
 *  19: Properties: YC
 *  20: Properties: BH
 *  21: Properties: Neutral
 *  22: Properties: (Fog)
 */

struct Palette_Data {

    // GL texture containing the palette.
    // GLuint texture;

    // Buffer containing the actual rows of palette data.
    Palette_Data_Row* buffer;

};