#pragma once

#include "Include/game.h"
#include "Game/Stage/stage.h"
#include "Game/Data/game_data.h"

typedef struct Game_Editor_Controller Game_Editor_Controller;

Game_Editor_Controller* create_game_editor_controller(
    Game_Data* game_data,
    Stage* stage,
    int* window_width,
    int* window_height
);

void free_game_editor_controller(Game_Editor_Controller* controller);