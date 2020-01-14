#pragma once

#include "Utilities/macros.h"

// All possible tiles
#define FOREACH_TILE_TYPE(TILE) \
    TILE(Plain) \
    TILE(Forest) \
    TILE(Mountain) \
    TILE(Road) \
    TILE(Bridge) \
    TILE(River) \
    TILE(Sea) \
    TILE(Reef) \
    TILE(Shore) \
    TILE(Pipe) \
    TILE(Pipe_Fragile) \
    TILE(Silo) \
    TILE(Base_Smoke) \
    TILE(Empty) \
    TILE(Land_Piece) \
    TILE(Property_HQ) \
    TILE(Property_City) \
    TILE(Property_Base) \
    TILE(Property_Airport) \
    TILE(Property_Port) \
    TILE(OOB) \

typedef enum {FOREACH_TILE_TYPE(GENERATE_ENUM)} Tile_Type;
static const char* tile_type_str[] = {FOREACH_TILE_TYPE(GENERATE_STRING)};
static const char* tile_type_str_short[] = {
"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T",
"U", "V", "W", "X", "Y", "Z"
};

#define NEUTRAL_TILE_TYPE_FIRST Plain
#define NEUTRAL_TILE_TYPE_LAST Land_Piece
#define NEUTRAL_TILE_TYPE_COUNT NEUTRAL_TILE_TYPE_LAST + 1

#define NEUTRAL_TILE_TYPE_BASIC_FIRST Plain
#define NEUTRAL_TILE_TYPE_BASIC_LAST Silo

#define PROPERTY_TILE_TYPE_FIRST Property_HQ
#define PROPERTY_TILE_TYPE_LAST  Property_Port
#define PROPERTY_TILE_TYPE_COUNT PROPERTY_TILE_TYPE_LAST + 1

#define TILE_TYPE_NONE -1

// Check if a tile type is neutral
#define is_tile_type_neutral(type) \
type >= NEUTRAL_TILE_TYPE_FIRST && type <= NEUTRAL_TILE_TYPE_LAST

// Check if a tile type is a property
#define is_tile_type_property(type) \
type >= PROPERTY_TILE_TYPE_FIRST && type <= PROPERTY_TILE_TYPE_LAST
