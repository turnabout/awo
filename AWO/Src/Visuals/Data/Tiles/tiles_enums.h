#pragma once
#include "Utils/macros.h"

// Tile Type
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
    TILE(PipeFragile) \
    TILE(Silo) \
    TILE(BaseSmoke) \
    TILE(LandPiece) \

typedef enum {FOREACH_TILE_TYPE(GENERATE_ENUM)} tile_type;
static const char* tile_type_str[] = {FOREACH_TILE_TYPE(GENERATE_STRING)};

#define TILE_TYPE_FIRST Plain
#define TILE_TYPE_LAST LandPiece
#define TILE_TYPE_AMOUNT TILE_TYPE_LAST + 1

// Tile Variation
#define FOREACH_TILE_VAR(TILEVAR) \
    TILEVAR(Default) \
    TILEVAR(Horizontal) \
    TILEVAR(Vertical) \
    TILEVAR(VerticalEnd) \
    TILEVAR(Top) \
    TILEVAR(Bottom) \
    TILEVAR(DirLeft) \
    TILEVAR(DirRight) \
    TILEVAR(TopLeft) \
    TILEVAR(TopRight) \
    TILEVAR(BottomLeft) \
    TILEVAR(BottomRight) \
    TILEVAR(Middle) \
    TILEVAR(ShadowedDefault) \
    TILEVAR(ShadowedTopLeft) \
    TILEVAR(ShadowedBottomLeft) \
    TILEVAR(ShadowedLeft) \
    TILEVAR(ShadowedHorizontal) \
    TILEVAR(ShadowedVertical) \
    TILEVAR(ShadowedVerticalEnd) \
    TILEVAR(ShadowedTLeft) \
    TILEVAR(TTop) \
    TILEVAR(TBottom) \
    TILEVAR(TLeft) \
    TILEVAR(TRight) \
    TILEVAR(Small) \
    TILEVAR(WaterfallUp) \
    TILEVAR(WaterfallDown) \
    TILEVAR(WaterfallLeft) \
    TILEVAR(WaterfallRight) \
    TILEVAR(Hole) \
    TILEVAR(HoleHorizontal) \
    TILEVAR(HoleVertical) \
    TILEVAR(HoleLeft) \
    TILEVAR(HoleRight) \
    TILEVAR(HoleTop) \
    TILEVAR(HoleBottom) \
    TILEVAR(TopConnectedLeft) \
    TILEVAR(TopConnectedRight) \
    TILEVAR(TopConnectedFull) \
    TILEVAR(BottomConnectedLeft) \
    TILEVAR(BottomConnectedRight) \
    TILEVAR(BottomConnectedFull) \
    TILEVAR(LeftConnectedTop) \
    TILEVAR(LeftConnectedBottom) \
    TILEVAR(LeftConnectedFull) \
    TILEVAR(RightConnectedTop) \
    TILEVAR(RightConnectedBottom) \
    TILEVAR(RightConnectedFull) \
    TILEVAR(TopLeftConnectedVertical) \
    TILEVAR(TopLeftConnectedHorizontal) \
    TILEVAR(TopLeftConnectedFull) \
    TILEVAR(TopRightConnectedVertical) \
    TILEVAR(TopRightConnectedHorizontal) \
    TILEVAR(TopRightConnectedFull) \
    TILEVAR(BottomLeftConnectedVertical) \
    TILEVAR(BottomLeftConnectedHorizontal) \
    TILEVAR(BottomLeftConnectedFull) \
    TILEVAR(BottomRightConnectedVertical) \
    TILEVAR(BottomRightConnectedHorizontal) \
    TILEVAR(BottomRightConnectedFull) \
    TILEVAR(HorizontalClosed) \
    TILEVAR(HorizontalOpen) \
    TILEVAR(VerticalClosed) \
    TILEVAR(VerticalOpen) \
    TILEVAR(Used) \

typedef enum {FOREACH_TILE_VAR(GENERATE_ENUM)} tile_var;
static const char* tile_var_str[] = {FOREACH_TILE_VAR(GENERATE_STRING)};

// Short versions of each tile variation string (used in JSON file to save space)
static char* tile_var_str_short[] = {
"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T",
"U", "V", "W", "X", "Y", "Z", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n",
"o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "0", "1", "2", "3", "4", "5", "6", "7",
"8", "9", ":", ";", "-", "="
};

#define TILE_VAR_FIRST Default
#define TILE_VAR_LAST Used
#define TILE_VAR_AMOUNT TILE_VAR_LAST + 1
