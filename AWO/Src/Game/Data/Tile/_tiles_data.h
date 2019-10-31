#pragma once

#include <cJSON.h>
#include <c_hashmap.h>

#include "Game/Data/Tile/Tile_Type_Data/_tile_type_data.h"
#include "Game/Data/Tile/Tile_Variation_Data/_tile_variation_data.h"
#include "Game/Data/Tile/enums.h"
#include "Game/Data/Tile/tiles_data.h"
#include "Game/Data/Animation/animation.h"
#include "Game/Clock/Animation_Clock/enums.h"

// All tiles' visual data
struct Tiles_Data
{
    Tile_Type_Data* src[TILE_TYPE_COUNT];
};
