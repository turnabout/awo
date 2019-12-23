#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "AWO.h"
#include "Game/Board/game_board.h"
#include "Game/Camera/game_camera.h"
#include "Game/Clock/game_clock.h"
#include "Game/Cursor/game_cursor.h"
#include "Game/Data/game_data.h"
#include "Game/Data/Palette/game_palette.h"
#include "Game/Editor/game_editor.h"
#include "Game/Inputs/inputs.h"
#include "Game/Renderer/game_renderer.h"

typedef struct Game Game;

struct Game {

    // Handle to the game's window.
    GLFWwindow* window;

    // Field holding all game data.
    Game_Data* data;

    // Dimensions of the game's window.
    int window_width, window_height;


    // Texture holding the palette data used during gameplay.
    GLuint palette_texture;

    // The game's editor, used in design room mode.
    Game_Editor* editor;

    // The game's board, containing and updating all current on-board game entities.
    Game_Board* board;

    // The game's camera, containing matrices used by the game's vertex shaders.
    Game_Camera* camera;

    // The game's clock used to update and synchronize entities' animations.
    Game_Clock* clock;

    // The game's renderer. Used to render all game elements.
    Game_Renderer* renderer;

    // The mouse's state.
    Mouse_State* mouse_state;

    // Pointer going over the currently hovered-over tile.
    Game_Cursor* cursor;

};

/*! @brief Initializes OpenGL and GLFW and sets related options.
 *
 *  @param[in] game The game object.
 *  @param[in] initial_window_width The initial game window's tiles_width.
 *  @param[in] initial_window_height The initial game window's tiles_height.
 *  @return TRUE if successful, FALSE if an error occurred.
 */
Bool init_GL(Game* game, int initial_window_width, int initial_window_height);

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
Bool prepare_game(Game* game, Stage* stage, CO_Type player_COs[MAX_PLAYER_COUNT]);

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