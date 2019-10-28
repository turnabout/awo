#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Game/game.h"
#include "Game/Data/Tile/tiles_data.h"
#include "Game/Sprite_Batch/sprite_batch.h"

struct Game {
    GLFWwindow* window;
    Sprite_Batch* sprite_batches[SPRITE_BATCH_TYPE_COUNT];

    Tiles_Data* tiles_data;

    int w, h;
};

/*! @brief Initializes the game data, storing on the main Game struct object.
 *
 *  @param[in] game The main game struct object.
 *  @param[in] sprite_sheet_w The width of the game's loaded sprite sheet.
 *  @param[in] sprite_sheet_h The height of the game's loaded sprite sheet.
 *  @return 1 if successful, 0 if an error occurred.
 */
int init_game_data(Game* game, int sprite_sheet_w, int sprite_sheet_h);