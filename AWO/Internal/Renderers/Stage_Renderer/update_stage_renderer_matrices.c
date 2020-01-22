#include "Renderers/Stage_Renderer/_stage_renderer.h"

// Identity matrix reference
static mat4 identity = GLM_MAT4_IDENTITY_INIT;

void update_stage_renderer_view(
    Stage_Renderer* renderer, 
    int view_x, 
    int view_y, 
    float view_zoom
)
{
    // Update tiles view matrix
    glm_translate_to(
        identity,
        (vec3) { (float)view_x, (float)view_y, 0.0f },
        renderer->tiles_view
    );

    glm_scale(
        renderer->tiles_view,
        (vec3) { view_zoom, view_zoom, 1.0f }
    );

    // Update units view matrix
    // TODO: offset vertically by correct amount
    glm_translate_to(
        identity,
        (vec3) { (float)view_x, (float)view_y, 0.0f },
        renderer->units_view
    );

    glm_scale(
        renderer->units_view,
        (vec3) { view_zoom, view_zoom, 1.0f }
    );
}

void update_stage_renderer_projection(Stage_Renderer* renderer, mat4 projection)
{
    glUseProgram(renderer->grids_shader_program);

    glUniformMatrix4fv(
        glGetUniformLocation(renderer->grids_shader_program, "projection"), 
        1, 
        GL_FALSE, 
        projection[0]
    );
}
