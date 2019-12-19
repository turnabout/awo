#include "Game/Renderer/_game_renderer.h"

static mat4 identity = GLM_MAT4_IDENTITY_INIT;

void update_game_renderer_view_matrices(
    Game_Renderer* renderer, 
    int view_x, 
    int view_y, 
    float view_zoom
)
{
    // Update tiles shader's view matrix
    mat4 tiles_shader_view;

    glm_translate_to(
        identity,
        (vec3) { (float)view_x, (float)view_y, 0.0f },
        tiles_shader_view
    );

    glm_scale(
        tiles_shader_view,
        (vec3) { view_zoom, view_zoom, 1.0f }
    );

    glUseProgram(renderer->tiles_shader_program);

    glUniformMatrix4fv(
        glGetUniformLocation(renderer->tiles_shader_program, "view"), 
        1, 
        GL_FALSE, 
        tiles_shader_view[0]
    );

    // TODO: update units shader's view matrix
    // TODO: update extras renderer's view matrix
}

void update_game_renderer_projection_matrices(Game_Renderer* renderer, int window_w, int window_h)
{
    // Update tiles shader's view matrix
    mat4 projection;

    glm_ortho(0.0f, (float)window_w, (float)window_h, 0.0f, -1.0f, 1.0f, projection);

    glUseProgram(renderer->tiles_shader_program);

    glUniformMatrix4fv(
        glGetUniformLocation(renderer->tiles_shader_program, "projection"), 
        1, 
        GL_FALSE, 
        projection[0]
    );
}
