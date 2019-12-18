#include <stdlib.h>

#include "Utilities/macros.h"
#include "GL_Helpers/gl_helpers.h"
#include "Game/Renderer/Extras_Renderer/extras_renderer.h"

struct Extras_Renderer {
    GLuint shader;
};

Extras_Renderer* create_extras_renderer()
{
    Extras_Renderer* renderer = malloc(sizeof(Extras_Renderer));
    
    renderer->shader = create_shader_program(
        VERTEX_SHADER_PATH(BASIC_SHADER),
        FRAGMENT_SHADER_PATH(BASIC_SHADER)
    );

    return renderer;
}

void free_extras_renderer(Extras_Renderer* renderer)
{
    if (renderer != NULL) {
        free(renderer);
    }
}