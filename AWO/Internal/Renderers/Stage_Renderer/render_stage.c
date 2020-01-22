#include "Renderers/Stage_Renderer/_stage_renderer.h"

static void inline update_grid_shader_view_matrix(Stage_Renderer* renderer, float* value)
{
    glUniformMatrix4fv(
        glGetUniformLocation(renderer->grids_shader_program, "view"), 
        1, 
        GL_FALSE, 
        value
    );
}

void render_stage(Stage_Renderer* renderer)
{
    // Render tile render grids
    glUseProgram(renderer->grids_shader_program);

    glActiveTexture(GL_TEXTURE0); 
    glBindTexture(GL_TEXTURE_2D, renderer->sprite_sheet_texture);

    glActiveTexture(GL_TEXTURE1); 
    glBindTexture(GL_TEXTURE_2D, renderer->palette_texture);

    // Render tile grids
    update_grid_shader_view_matrix(renderer, renderer->tiles_view[0]);
    render_r_grid(renderer->grid_layers[TILE_LAYER_0]);
    render_r_grid(renderer->grid_layers[TILE_LAYER_1]);

    // Render unit grids
    // update_grid_shader_view_matrix(renderer, renderer->units_view[0]);
    // render_r_grid(renderer->grid_layers[UNIT_LAYER]);
}
