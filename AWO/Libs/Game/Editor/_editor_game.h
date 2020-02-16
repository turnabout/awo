#pragma once

#include "Include/emx.h"
#include "Camera/camera.h"
#include "Clock/clock.h"
#include "Game_Data/game_data.h"
#include "Game/Editor/editor_game.h"
#include "Game_Window/game_window.h"
#include "Game/_game.h"
#include "Palette/palette.h"
#include "Renderers/Extras_Renderer/extras_renderer.h"
#include "Renderers/Stage_Renderer/stage_renderer.h"
#include "GL_Helpers/gl_helpers.h"
#include "Input_Handlers/Keyboard_Handler/keyboard_handler.h"
#include "Input_Handlers/Mouse_Handler/mouse_handler.h"

struct Editor_Game {

    // Function used to update the game.
    Game_Update_CB update;

    // Function used to render the game.
    Game_Render_CB render;

    // Function used to update the game's dimensions internally.
    Game_Dimensions_Update_CB update_dimensions;

    // Current inputs state.
    Keyboard_State* keyboard_state;
    Mouse_State* mouse_state;

    // Collection of all game data modules.
    Game_Data* data;

    // Currently loaded stage.
    Stage* stage;

    // The game camera module.
    Camera* camera;

    // The game clock module.
    Clock* clock;

    // Module used to render the stage.
    Stage_Renderer* stage_renderer;

    // Module used to render extra elements.
    Extras_Renderer* extras_renderer;

    // The game palette used for this game.
    GLuint palette;

    // The sprite sheet texture used for this game.
    GLuint sprite_sheet;

};

void update_editor_game(Editor_Game* game, float delta_time);
void render_editor_game(Editor_Game* game);
void update_editor_game_dimensions(Game* game, int window_width, int window_height);