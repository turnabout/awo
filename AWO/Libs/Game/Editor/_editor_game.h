#pragma once

#include "Camera/camera.h"
#include "Clock/game_clock.h"
#include "Game_Data/game_data.h"
#include "Game/Editor/editor_game.h"
#include "Game_Window/game_window.h"
#include "Game/_game.h"
#include "Renderers/Extras_Renderer/extras_renderer.h"
#include "Include/emx.h"
// #include "Renderer/Stage_Renderer/stage_renderer.h"

struct Editor_Game {

    // Function used to update the game.
    Game_Update_CB update;

    // Function used to render the game.
    Game_Render_CB render;

    // Collection of all game data modules.
    Game_Data* data;

    // Currently loaded stage.
    Stage* stage;

    // The game camera module.
    Camera* camera;

    // The game clock module.
    Game_Clock* clock;

    // Module used to render the stage.
    // Stage_Renderer* stage_renderer;

    // Module used to render extra elements.
    Extras_Renderer* extras_renderer;

    // The game palette used for this game.
    GLuint palette;

};

void update_editor_game(Editor_Game* game, float delta_time);
void render_editor_game(Editor_Game* game);
