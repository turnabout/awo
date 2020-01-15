#pragma once

#include "Internal/Camera/camera.h"
#include "Game/Clock/game_clock.h"
#include "Game/Stage/stage.h"
#include "Game/Controller/Editor/game_editor_controller.h"

/*! @brief Game update callback function. Handled by the game's controller.
 */
typedef void (*Game_Update_CB)(void* game_controller, float delta_time);

/*! @brief Game render callback function. Handled by the game's controller.
 */
typedef void (*Game_Render_CB)(void* game_controller);

typedef struct Game_Controller {

    // Update function.
    Game_Update_CB update;

    // Render function.
    Game_Render_CB render;

} Game_Controller;