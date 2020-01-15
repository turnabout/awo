#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include "Game/Data/Animation/Frame/frame.h"

/*! @brief Used to render extra elements in the game.
 *
 *  @note Extra elements are visual elements that are rendered on top of the main render grids.
 *  Unlike main UI components, they are affected by the same view coordinates as the render grids.
 */
typedef struct Extras_Renderer Extras_Renderer;

Extras_Renderer* create_extras_renderer(GLuint sprite_sheet);

void update_extras_renderer_view(Extras_Renderer* renderer, int x, int y, float zoom);
void update_extras_renderer_projection(Extras_Renderer* renderer, mat4 projection);

void queue_extra_renderer_extra(Extras_Renderer* renderer, vec2 dst, Frame* frame);
void render_queued_extra_renderer_extras(Extras_Renderer* renderer);

void free_extras_renderer(Extras_Renderer* renderer);