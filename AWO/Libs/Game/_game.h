#pragma once

// Includes
#include "types.h"
#include "emx.h"
#include "Game/game.h"

// Libs
#include "../Game_Message/game_message.h"

// Local
#include "./Headers/game_callback_types.h"

struct Game {

    // Function used to update the game.
    Game_Update_CB update;

    // Function used to render the game.
    Game_Render_CB render;

    // Function used to update the game's dimensions internally.
    Game_Dimensions_Update_CB update_dimensions;

};
