#include "Game/Renderer/_game_renderer.h"

void inline update_grid_shader_view_matrix(Game_Renderer* renderer, float* value)
{

    glUniformMatrix4fv(
        glGetUniformLocation(renderer->grid_shader, "view"), 
        1, 
        GL_FALSE, 
        value
    );
}

void render_game_renderer_grids(Game_Renderer* renderer)
{
    // Render tile render grids
    glUseProgram(renderer->grid_shader);

    glActiveTexture(GL_TEXTURE0); 
    glBindTexture(GL_TEXTURE_2D, renderer->sprite_sheet_texture);

    glActiveTexture(GL_TEXTURE1); 
    glBindTexture(GL_TEXTURE_2D, renderer->game_palette_texture);

    update_grid_shader_view_matrix(renderer, renderer->tiles_view[0]);

    render_r_grid(renderer->grid_layers[TILE_LAYER_0]);
    render_r_grid(renderer->grid_layers[TILE_LAYER_1]);

    // Render unit render grids
    update_grid_shader_view_matrix(renderer, renderer->units_view[0]);
    render_r_grid(renderer->grid_layers[UNIT_LAYER]);
}

void queue_extra(Game_Renderer* renderer, vec2 dst, Frame* frame)
{
    queue_extra_renderer_extra(renderer->extras_renderer, dst, frame);
}

void render_extras(Game_Renderer* renderer)
{
    render_queued_extra_renderer_extras(renderer->extras_renderer);
}
