#pragma once

#include "Include/emx.h"
#include "Include/Game/game.h"
#include "Game/Headers/game_callback_types.h"
#include "Game_Data/game_data.h"
#include "Game_Message/game_message.h"
#include "Game_Window/game_window.h"

struct Game {

    // Function used to update the game.
    Game_Update_CB update;

    // Function used to render the game.
    Game_Render_CB render;

};