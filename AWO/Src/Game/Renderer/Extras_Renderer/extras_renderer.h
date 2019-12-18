#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

/*! @brief Used to render extra elements in the game.
 */
typedef struct Extras_Renderer Extras_Renderer;

Extras_Renderer* create_extras_renderer();

void update_extras_renderer_matrices();

void free_extras_renderer(Extras_Renderer* renderer);