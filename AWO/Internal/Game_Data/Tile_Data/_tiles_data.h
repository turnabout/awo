#pragma once

#include "Game/Data/Tile/Neutral_Tile/_neutral_tiles_data.h"
#include "Game/Data/Tile/Property_Tile/_property_tiles_data.h"
#include "Game/Data/Tile/tiles_data.h"

struct Tiles_Data
{
    Neutral_Tiles_Data* neutral_tiles;
    Property_Tiles_Data* property_tiles;
};
