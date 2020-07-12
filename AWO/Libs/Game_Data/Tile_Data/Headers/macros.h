#pragma once

#include "Game_Data/Tile_Data/Tile_Type_Data/tile_type_data.h"

// Check if a tile type is neutral
#define is_tile_type_neutral(type) \
type >= NEUTRAL_TILE_TYPE_FIRST && type <= NEUTRAL_TILE_TYPE_LAST

// Check if a tile type is a property
#define is_tile_type_property(type) \
type >= PROPERTY_TILE_TYPE_FIRST && type <= PROPERTY_TILE_TYPE_LAST
