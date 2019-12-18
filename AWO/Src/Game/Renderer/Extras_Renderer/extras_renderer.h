#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include "Game/Data/Animation/Frame/frame.h"

/*! @brief Used to render extra elements in the game.
 */
typedef struct Extras_Renderer Extras_Renderer;

Extras_Renderer* create_extras_renderer();

void update_extras_renderer_matrices(Extras_Renderer* renderer, mat4 matrix);
void queue_extra_item_render(Extras_Renderer* renderer, vec2 dst, Frame* frame);

void free_extras_renderer(Extras_Renderer* renderer);