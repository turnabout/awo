#pragma once

#include "Game_Data/Tile_Data/Tile_Type_Data/tile_type_data.h"
#include "Game_Data/Property_Data/property_data.h"

// Convert a property tile type to a property type
#define tile_to_property(type) \
(type - PROPERTY_TILE_TYPE_FIRST)
