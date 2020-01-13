#pragma once

#include "Camera/camera.h"
#include "Game/Controller/Editor/game_editor_controller.h"
#include "Game/Clock/game_clock.h"
#include "Game/Renderer/Stage_Renderer/stage_renderer.h"
#include "Game/Renderer/Extras_Renderer/extras_renderer.h"
#include "Game/Data/Palette/game_palette.h"

struct Game_Editor_Controller {

    // Currently loaded stage.
    Stage* stage;

    // The game camera module.
    Camera* camera;

    // The game clock module.
    Game_Clock* clock;

    // Module used to render the stage.
    Stage_Renderer* stage_renderer;

    // Module used to render extra elements.
    Extras_Renderer* extras_renderer;

    // The game palette used for this game.
    GLuint palette;

};