#pragma once

#include "Game/Data/Animation/animation.h"
#include "Game/Data/Tile/tiles_data.h"
#include "Game/Clock/game_clock.h"
#include "types.h"

typedef struct Neutral_Tile {

    // This tile's animation.
    Animation* animation;

    // The coordinates of every instances of this tile present in the game.
    Point* positions;

    // This tile's type.
    Tile_Type type;

    // This tile's variation.
    Tile_Variation variation;

    // How many instances of this tile exist in the game.
    Uint16 count;

} Neutral_Tile;

Neutral_Tile* create_neutral_tile(
    Game_Clock* game_clock,
    Neutral_Tiles_Data* tiles_data,
    Tile_Type type, 
    Tile_Variation variation
);