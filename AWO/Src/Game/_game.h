#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Include/game.h"
#include "Utilities/Message_Service/message_service.h"
#include "Game/Board/game_board.h"
#include "Game/Camera/game_camera.h"
#include "Game/Clock/game_clock.h"
#include "Game/Cursor/game_cursor.h"
#include "Game/Data/game_data.h"
#include "Game/Data/Palette/game_palette.h"
#include "Game/Editor/game_editor.h"
#include "Game/Inputs/inputs.h"
#include "Game/Renderer/game_renderer.h"
#include "Game/Controller/game_controller.h"

struct Game {

    // The game's current state.
    Game_State state;

    // The game's current mode.
    Game_Mode mode;

    // Collection of all game data modules.
    Game_Data* data;

    // Handle to the game's window.
    GLFWwindow* window;

    // Dimensions of the game's window.
    int window_width, window_height;

    // Current controller used to update & render the game.
    Game_Controller* controller;


    // The game's board, containing and updating all current on-board game entities.
    Game_Board* board;

    // The game's camera, containing matrices used by the game's vertex shaders.
    Game_Camera* camera;

    // Pointer going over the currently hovered-over tile.
    Game_Cursor* cursor;

    // The game's clock used to update and synchronize entities' animations.
    Game_Clock* clock;

    // The game's editor, used in design room mode.
    Game_Editor* editor;

    // The mouse's state.
    Mouse_State* mouse_state;

    // The game's renderer. Used to render all game elements.
    Game_Renderer* renderer;

    // Texture holding the palette data used during gameplay.
    GLuint palette;

};

/*! @brief Initializes OpenGL and GLFW and sets related options.
 *
 *  @param[in] game The game object.
 *  @return TRUE if successful, FALSE if an error occurred.
 */
Bool init_GL(Game* game);

/*! @brief Initializes game rendering-related settings.
 *
 *  @param[in] game The game object.
 *  @param[in] window_width Initial width of the window.
 *  @param[in] window_height Initial height of the window.
 *  @return TRUE if successful, FALSE if an error occurred.
 */
Bool init_game_rendering(Game* game, int window_width, int window_height);

/*! @brief Prepares the game for gameplay.
 *
 * Loads the game board using the given stage and player COs data & also sets components vital to
 * gameplay.
 *
 *  @param[in] game The game object.
 *  @param[in] stage The stage to load.
 *  @param[in] player_COs The players' COs.
 *  @return TRUE if successful, FALSE if an error occurred.
 */
//Bool prepare_game(Game* game, Stage* stage, CO_Type player_COs[MAX_PLAYER_COUNT]);

/*! @brief Updates the game's entities.
 *
 *  @param[in] game The game object.
 *  @param[in] delta_time Elapsed seconds since last frame.
 */
void update_game(Game* game, float delta_time);

/*! @brief Renders the game's entities.
 *
 *  @param[in] game The game object.
 */
void render_game(Game* game);