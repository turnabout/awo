#include "Game/Renderer/_game_renderer.h"

void render_game_renderer(Game_Renderer* renderer)
{
    // Render tile render grids
    glUseProgram(renderer->tiles_shader_program);

    glActiveTexture(GL_TEXTURE0); 
    glBindTexture(GL_TEXTURE_2D, renderer->sprite_sheet_texture);

    glActiveTexture(GL_TEXTURE1); 
    glBindTexture(GL_TEXTURE_2D, renderer->game_palette_texture);

    render_r_grid(renderer->grid_layers[TILE_LAYER_0]);
    render_r_grid(renderer->grid_layers[TILE_LAYER_1]);

    // TODO: Render extras
}
