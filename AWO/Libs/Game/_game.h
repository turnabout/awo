#pragma once

#include "Include/types.h"
#include "Include/emx.h"
#include "Include/Game/game.h"
#include "Game/Headers/game_callback_types.h"
#include "Game_Message/game_message.h"

struct Game {

    // Function used to update the game.
    Game_Update_CB update;

    // Function used to render the game.
    Game_Render_CB render;

    // Function used to update the game's dimensions internally.
    Game_Dimensions_Update_CB update_dimensions;

};
