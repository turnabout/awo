#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Game/Stage/stage.h"
#include "Game/Data/game_data.h"

typedef struct Stage_Renderer Stage_Renderer;

Stage_Renderer* create_stage_renderer(Stage* stage, Game_Data* game_data);

void update_stage_renderer_view(
    Stage_Renderer* renderer,
    int view_x,
    int view_y,
    float view_zoom
);

void update_stage_renderer_projection(Stage_Renderer* renderer, mat4 projection);

void free_stage_renderer(Stage_Renderer* renderer);