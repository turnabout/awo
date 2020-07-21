#pragma once

#include "AWO/types.h"
#include "AWO/emx.h"
#include "Game/game.h"
#include "Game/Headers/game_callback_types.h"
#include "Game_Message/game_message.h"
#include "Game_Data/game_data.h"
#include "Input_State/input_state.h"
#include "Camera/camera.h"
#include "Clock/clock.h"
#include "Renderers/renderers.h"
#include "Input_Handlers/input_handlers.h"
#include "Game_Window/game_window.h"
#include "Palette/palette.h"

/**
 * All play modes the game can possibly have.
 */
typedef enum Game_Mode
{
    GAME_MODE_VERSUS,
    GAME_MODE_DESIGN_ROOM
} Game_Mode;

struct Game {

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

    // Function used to update the game.
    Game_Update_CB update;

    // Function used to render the game.
    Game_Render_CB render;

    // Function used to update the game's dimensions internally.
    Game_Dimensions_Update_CB update_dimensions;

};
