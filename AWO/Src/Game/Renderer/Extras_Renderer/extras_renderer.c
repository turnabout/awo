#include <stdlib.h>

#include "conf.h"
#include "Utilities/macros.h"
#include "GL_Helpers/gl_helpers.h"
#include "Game/Renderer/Extras_Renderer/extras_renderer.h"
#include "Game/Renderer/Sprite_Batch/sprite_batch.h"

// Identity matrix reference
mat4 identity = GLM_MAT4_IDENTITY_INIT;

struct Extras_Renderer {

    // Shader program used to render extras.
    GLuint shader;

    // Sprite batch used to render extras.
    Sprite_Batch* sprite_batch;

    // Whether an extra has been queued for rendering.
    Bool extra_queued;

};

Extras_Renderer* create_extras_renderer(GLuint sprite_sheet)
{
    Extras_Renderer* renderer = malloc(sizeof(Extras_Renderer));

    renderer->extra_queued = FALSE;
    
    // Create the shader program
    renderer->shader = create_shader_program(
        VERTEX_SHADER_PATH(BASIC_SHADER),
        FRAGMENT_SHADER_PATH(BASIC_SHADER)
    );

    renderer->sprite_batch = create_sprite_batch(
        renderer->shader,
        sprite_sheet,
        0,
        10 // TODO: un-hardcode
    );

    return renderer;
}

void update_extras_renderer_view(Extras_Renderer* renderer, int x, int y, float zoom)
{
    // Update tiles shader's view matrix
    mat4 view;

    glm_translate_to(
        identity,
        (vec3) { (float)x, (float)y, 0.0f },
        view
    );

    // The zoom this function receives is the zoom applied to the game renderer's grids.
    // The zoom that should be applied to extras is different: an x16 (x DEFAULT_TILE_SIZE) zoom 
    // applied to grids is the equivalent of an x1 zoom applied to extra elements.
    float real_zoom = zoom / (float)DEFAULT_TILE_SIZE;

    glm_scale(
        view,
        (vec3) { real_zoom, real_zoom, 1.0f }
    );

    glUseProgram(renderer->shader);

    glUniformMatrix4fv(
        glGetUniformLocation(renderer->shader, "view"), 
        1, 
        GL_FALSE, 
        view[0]
    );
}

void update_extras_renderer_projection(Extras_Renderer* renderer, mat4 projection)
{
    glUseProgram(renderer->shader);

    glUniformMatrix4fv(
        glGetUniformLocation(renderer->shader, "projection"), 
        1, 
        GL_FALSE, 
        projection[0]
    );
}

void queue_extra_renderer_extra(Extras_Renderer* renderer, vec2 dst, Frame* frame)
{
    if (!renderer->extra_queued) {
        renderer->extra_queued = TRUE;
        begin_sprite_batch(renderer->sprite_batch);
    }

    add_to_sprite_batch(renderer->sprite_batch, dst, frame, 0);
}

void render_queued_extra_renderer_extras(Extras_Renderer* renderer)
{
    if (renderer->extra_queued) {
        end_sprite_batch(renderer->sprite_batch);
        renderer->extra_queued = FALSE;
    }
}

void free_extras_renderer(Extras_Renderer* renderer)
{
    if (renderer != NULL) {
        free(renderer);
    }
}