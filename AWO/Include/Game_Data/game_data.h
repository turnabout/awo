#pragma once

#include "clock_data.h"
#include "CO_data.h"
#include "tile_data.h"
#include "property_data.h"
#include "unit_data.h"
#include "UI_data.h"
#include "palette_data.h"
#include "weather.h"
#include "army_types.h"

#define MAX_LOADED_STAGE_COUNT 16

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

    // For for all all palettes.
    Palette_Data* palette;

    // Default stages.
    char* default_stages[MAX_LOADED_STAGE_COUNT];

    // Holds the game's sprite sheet's texture.
    unsigned int sprite_sheet;

    // The game's sprite sheet's dimensions.
    int sprite_sheet_width, sprite_sheet_height;

} Game_Data;

Game_Data* create_game_data();

void free_game_data(Game_Data* game_data);
