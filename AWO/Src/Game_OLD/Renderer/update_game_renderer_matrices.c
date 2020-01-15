#include "Game/Renderer/_game_renderer.h"

// Identity matrix reference
static mat4 identity = GLM_MAT4_IDENTITY_INIT;

void update_game_renderer_view_matrices(
    Game_Renderer* renderer, 
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

    // Update extras renderer's view matrix
    update_extras_renderer_view(renderer->extras_renderer, view_x, view_y, view_zoom);
}

void update_game_renderer_projection_matrices(Game_Renderer* renderer, int window_w, int window_h)
{
    // Update grid shader's view matrix
    mat4 projection;

    glm_ortho(0.0f, (float)window_w, (float)window_h, 0.0f, -1.0f, 1.0f, projection);

    glUseProgram(renderer->grid_shader);

    glUniformMatrix4fv(
        glGetUniformLocation(renderer->grid_shader, "projection"), 
        1, 
        GL_FALSE, 
        projection[0]
    );

    // Update extras renderer's projection matrix
    update_extras_renderer_projection(renderer->extras_renderer, projection);
}
