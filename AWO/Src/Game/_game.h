#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Game/game.h"
#include "Game/Board/game_board.h"
#include "Game/Camera/game_camera.h"
#include "Game/Clock/game_clock.h"
#include "Game/Data/Tile/tiles_data.h"
#include "Game/Data/Unit/units_data.h"
#include "Game/Data/UI/UI_data.h"
#include "Game/Editor/game_editor.h"
#include "Game/Inputs/inputs.h"
#include "Game/Renderer/game_renderer.h"

struct Game {

    // Handle to the game's window.
    GLFWwindow* window;

    // The game's board, containing and updating all current on-board game entities.
    Game_Board* board;

    // The game's camera, containing matrices used by the game's vertex shaders.
    Game_Camera* camera;

    // The game's clock used to update and synchronize entities' animations.
    Game_Clock* clock;

    // The game's editor, used in design room mode.
    Game_Editor* editor;

    // Data for all tiles.
    Tiles_Data* tiles_data;

    // Data for all units.
    Units_Data* units_data;

    // Data for all UI elements.
    UI_Data* UI_data;

    // Initially loaded default stages.
    Stage* stages[MAX_LOADED_STAGE_COUNT];

    // The mouse's state.
    Mouse_State* mouse_state;

    // Dimensions of the game's window.
    int window_width, window_height;

    // Texture holding all palette data.
    GLuint raw_palette_texture;

    // Texture holding the palette data used during gameplay.
    GLuint palette_texture;
};

/*! @brief Initializes OpenGL and GLFW and sets related options.
 *
 *  @param[in] game The game object.
 *  @param[in] initial_window_width The initial game window's tiles_width.
 *  @param[in] initial_window_height The initial game window's tiles_height.
 *  @return TRUE if successful, FALSE if an error occurred.
 */
Bool init_GL(Game* game, int initial_window_width, int initial_window_height);

/*! @brief Initializes the game data and modules using it, attaching results to the game object.
 *
 *  @param[in] game The game object.
 *  @return TRUE if successful, FALSE if an error occurred.
 */
Bool init_game_data(Game* game);

/*! @brief Updates the game's entities.
 *
 *  @param[in] game The game object.
 *  @param[in] delta_time Elapsed seconds since last frame.
 */
void update_game(Game* game, float delta_time);

/*! @brief Updates the game's window dimensions.
 *
 *  @param[in] game The game object.
 *  @param[in] width The new window width.
 *  @param[in] height The new window height.
 */
void update_game_window_dimensions(Game* game, int width, int height);

/*! @brief Renders the game's entities.
 *
 *  @param[in] game The game object.
 */
void render_game(Game* game);