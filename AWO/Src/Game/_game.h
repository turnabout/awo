#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Game/game.h"
#include "Game/Board/game_board.h"
#include "Game/Data/Tile/tiles_data.h"
#include "Game/Data/Unit/units_data.h"
#include "Game/Clock/game_clock.h"
#include "Game/Sprite_Batch/sprite_batch.h"

struct Game {
    GLFWwindow* window;
    Sprite_Batch* sprite_batches[SPRITE_BATCH_TYPE_COUNT];

    Tiles_Data* tiles_data;
    Units_Data* units_data;
    GLuint      palette_texture;

    Game_Board* board;
    Game_Clock* clock;

    int w, h;
};

/*! @brief Initializes the game data and modules using it, attaching results to the game object.
 *
 *  @param[in] game The main game struct object.
 *  @return 1 if successful, 0 if an error occurred.
 */
int init_game_data(Game* game);