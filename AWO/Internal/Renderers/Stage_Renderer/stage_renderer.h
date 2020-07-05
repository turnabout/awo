#pragma once

#include <cglm/cglm.h>

#include "Stage/stage.h"
#include "AWO/game_data.h"

typedef struct Stage_Renderer Stage_Renderer;

Stage_Renderer* create_stage_renderer(
    Stage* stage,
    GLuint palette,
    GLuint sprite_sheet,
    Game_Data* game_data
);

void render_stage(Stage_Renderer* renderer);

void update_stage_renderer_view(
    Stage_Renderer* renderer,
    int view_x,
    int view_y,
    float view_zoom
);

void update_stage_renderer_projection(Stage_Renderer* renderer, mat4 projection);

void free_stage_renderer(Stage_Renderer* renderer);