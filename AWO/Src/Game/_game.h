#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "game.h"
#include "Game/Board/game_board.h"
#include "Game/Camera/game_camera.h"
#include "Game/Clock/game_clock.h"
#include "Game/Cursor/game_cursor.h"
#include "Game/Data/game_data.h"
#include "Game/Editor/game_editor.h"
#include "Game/Inputs/inputs.h"
#include "Game/Renderer/game_renderer.h"

typedef struct Game Game;
typedef enum Game_State Game_State;

struct Game {

    // 1. Game_Initialized fields
    // Handle to the game's window.
    GLFWwindow* window;

    // Field holding all game data.
    Game_Data* data;

    // Dimensions of the game's window.
    int window_width, window_height;

    // Current game's state.
    Game_State state;

    // 2. Game_Prepared fields
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
    Game_Cursor* pointer;

};

/*! @brief Initializes OpenGL and GLFW and sets related options.
 *
 *  @param[in] game The game object.
 *  @param[in] initial_window_width The initial game window's tiles_width.
 *  @param[in] initial_window_height The initial game window's tiles_height.
 *  @return TRUE if successful, FALSE if an error occurred.
 */
Bool init_GL(Game* game, int initial_window_width, int initial_window_height);

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