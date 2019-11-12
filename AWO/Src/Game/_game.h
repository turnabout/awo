#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Game/game.h"
#include "Game/Board/game_board.h"
#include "Game/Clock/game_clock.h"
#include "Game/Data/Tile/tiles_data.h"
#include "Game/Data/Unit/units_data.h"
#include "Game/Inputs/inputs.h"
#include "Game/Renderer/game_renderer.h"

struct Game {

    // Handle to the game's window.
    GLFWwindow* window;

    // Dimensions of the game's window.
    int window_width, window_height;

    // Game renderer, responsible for rendering all of the game's on-screen entities.
    Game_Renderer* renderer;

    // The game's board, containing and updating all current on-board game entities.
    Game_Board* board;

    // The game's clock used to update and synchronize entities' animations.
    Game_Clock* clock;

    // Module subscribed to the game clock. Used to tell tiles of certain type/variation when they
    // need to update their sections of the render map.
    Tiles_Clock_Subscriber* tiles_clock_sub;

    // Data for all tiles.
    Tiles_Data* tiles_data;

    // Data for all units.
    Units_Data* units_data;

    // Texture object for palettes
    GLuint palettes_texture;
};

/*! @brief Initializes OpenGL and GLFW and sets related options.
 *
 *  @param[in] game The game object.
 *  @param[in] initial_window_width The initial game window's tiles_width.
 *  @param[in] initial_window_height The initial game window's tiles_height.
 *  @return 1 if successful, 0 if an error occurred.
 */
int init_GL(Game* game, int initial_window_width, int initial_window_height);

/*! @brief Initializes the game data and modules using it, attaching results to the game object.
 *
 *  @param[in] game The game object.
 *  @return 1 if successful, 0 if an error occurred.
 */
int init_game_data(Game* game);

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