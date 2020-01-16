#pragma once

#include "Stage/stage.h"
#include "Game_Data/Animation/animation.h"
#include "Game_Data/Frame/frame.h"
#include "Game_Data/Clock_Data/clock_data.h"
#include "Game_Data/Palette_Data/palette_data.h"
#include "Game_Data/Unit_Data/unit_data.h"
#include "Game_Data/Tile_Data/tile_data.h"
#include "Game_Data/Property_Data/property_data.h"
#include "Game_Data/UI_Data/UI_data.h"
#include "Game_Data/CO_Data/CO_data.h"
#include "Headers/army_types.h"
#include "Headers/weather.h"

typedef struct Game_Data {

    // Data for clocks used for animations among other things.
    Clock_Data* clock;

    // Data for all COs.
    CO_Data* CO;

    // Data for all tiles.
    Tile_Data* tile;

    // Data for all properties.
    Property_Data* property;

    // Data for all units.
    Unit_Data* unit;

    // Data for all UI elements.
    UI_Data* UI;

    // Default stages.
    char* default_stages[MAX_LOADED_STAGE_COUNT];

    // For for all all palettes.
    Palette_Data* palette;

    // Holds the game's sprite sheet's texture.
    GLuint sprite_sheet;

    // The game's sprite sheet's dimensions.
    int sprite_sheet_width, sprite_sheet_height;

} Game_Data;

Game_Data* create_game_data();

void free_game_data(Game_Data* game_data);