#pragma once

#include "Game_Data/Animation/animation.h"
#include "Game_Data/Frame/frame.h"
#include "Game_Data/Clock/clock_data.h"
#include "Game_Data/Palette/raw_palette.h"
#include "Game_Data/Units_Data/units_data.h"
#include "Game_Data/Tiles_Data/tiles_data.h"
#include "Game_Data/UI_Data/UI_data.h"
#include "Game_Data/COs_Data/COs_data.h"
#include "Stage/stage.h"

typedef struct Game_Data {

    // Data for clocks used for animations among other things.
    Clock_Data* clock;

    // Data for all COs.
    CO_Data* CO;

    // Data for all tiles.
    Tiles_Data* tiles;

    // Data for all units.
    Units_Data* units;

    // Data for all UI elements.
    UI_Data* UI;

    // Initially loaded default stages.
    Stage* stages[MAX_LOADED_STAGE_COUNT];

    // Texture holding all palette data.
    GLuint raw_palette;

    // Holds the game's sprite sheet's texture.
    GLuint sprite_sheet;

    // The game's sprite sheet's dimensions.
    int sprite_sheet_width, sprite_sheet_height;

} Game_Data;

Game_Data* create_game_data();

void free_game_data(Game_Data* game_data);