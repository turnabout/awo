#pragma once

#include <AWO/types.h>
#include "Game_Data/Sprite_Sheet_Data/sprite_sheet_data.h"

struct Sprite_Sheet_Data {

    // Sprite sheet's dimensions.
    int width, height;

    // Amount of channels the sprite sheet image has.
    int channels_amount;

    // Buffer containing the sprite sheet's pixel data in RGBA format.
    Uint8* buffer;

};