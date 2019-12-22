#pragma once

#include "Game/Data/Clock/clock_data.h"
#include "Game/Data/Palette/raw_palette.h"
#include "Game/Data/Unit/units_data.h"
#include "Game/Data/Tile/tiles_data.h"
#include "Game/Data/UI/UI_data.h"
#include "Game/Data/CO/CO_data.h"
#include "Game/Stage/stage.h"

typedef struct Game_Data {

    // Data for clocks used for animations among other things.
    Clock_Data* clock_data;

    // Data for all COs.
    CO_Data* CO_data;

    // Data for all tiles.
    Tiles_Data* tiles_data;

    // Data for all units.
    Units_Data* units_data;

    // Data for all UI elements.
    UI_Data* UI_data;

    // Initially loaded default stages.
    Stage* stages[MAX_LOADED_STAGE_COUNT];

    // Texture holding all palette data.
    GLuint raw_palette;

    // Holds the game's sprite sheet's texture.
    GLuint sprite_sheet;

} Game_Data;

Game_Data* create_game_data();

void free_game_data(Game_Data* game_data);