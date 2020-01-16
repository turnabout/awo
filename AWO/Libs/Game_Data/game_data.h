#pragma once

#include "Include/Game_Data/game_data.h"
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

Game_Data* create_game_data();

void free_game_data(Game_Data* game_data);