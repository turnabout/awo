#pragma once

#include "Game/Data/Tile/Type/_tile_type_data.h"
#include "Game/Data/Tile/tiles_data.h"

struct Tiles_Data
{
    Tile_Type_Data* src[TILE_TYPE_COUNT];
};
