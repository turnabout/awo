#pragma once

#include "Game_Data/Animation/animation.h"
#include "Game_Data/Clock_Data/clock_data.h"
#include "Game_Data/Tile_Data/Tile_Variation_Data/tile_variation_data.h"

struct Tile_Variation_Data {

    // Index to the clock used by this tile variation to update its animation.
    Clock_Index clock;

    // This tile variation's animation.
    Animation* animation;

};