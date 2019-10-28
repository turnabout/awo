#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Game/game.h"
#include "Game/Sprite_Batch/sprite_batch.h"

struct Game {
    GLFWwindow* window;
    Sprite_Batch* sprite_batches[SPRITE_BATCH_TYPE_COUNT];
    int w, h;
};