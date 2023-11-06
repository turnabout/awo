#pragma once

// Libs
#include "../../Animation/animation.h"
#include "../../Clock_Data/clock_data.h"
#include "../../Tile_Data/Tile_Variation_Data/tile_variation_data.h"

struct Tile_Variation_Data {

    // Index to the clock used by this tile variation to update its animation.
    Clock_Index clock;

    // This tile variation's animation.
    Animation* animation;

};