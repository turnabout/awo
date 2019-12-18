#include "Game/Renderer/_game_renderer.h"

static Game_Renderer* renderer;

void init_game_renderer(
    int grid_width, 
    int grid_height, 
    GLuint game_palette_texture,
    Tiles_Data* tiles_data
)
{
    renderer = _init_game_renderer(grid_width, grid_height, game_palette_texture, tiles_data);
}

void render_game_renderer()
{
    // Render the tile render grids
    glUseProgram(renderer->tiles_shader_program);

    glActiveTexture(GL_TEXTURE0); 
    glBindTexture(GL_TEXTURE_2D, renderer->sprite_sheet_texture);

    glActiveTexture(GL_TEXTURE1); 
    glBindTexture(GL_TEXTURE_2D, renderer->game_palette_texture);

    render_r_grid(renderer->tile_grid_layers[TILE_LAYER_0]);
    render_r_grid(renderer->tile_grid_layers[TILE_LAYER_1]);
}

void update_game_renderer_matrix(mat4 matrix, const char* matrix_str)
{
    // Update tiles shader's given matrix
    glUseProgram(renderer->tiles_shader_program);

    glUniformMatrix4fv(
        glGetUniformLocation(renderer->tiles_shader_program, matrix_str), 
        1, 
        GL_FALSE, 
        matrix[0]
    );
}

void clear_tile_layers_pixel(Uint8 x, Uint8 y)
{
    for (int i = 0; i < TILE_LAYER_TYPE_COUNT; i++) {
        update_render_grid_pixel_low(
            renderer->tile_grid_layers[i],
            x,
            y,
            (vec2) {
                renderer->empty_tile_frame->frames[0].raw_top_left[0],
                renderer->empty_tile_frame->frames[0].raw_top_left[1],
            }
        );
    }
}

void update_tile_layer_pixel(Tile_Layer_Index layer, Uint8 x, Uint8 y, vec4 value)
{
    update_render_grid_pixel(renderer->tile_grid_layers[layer], x, y, value);
}

void update_tile_layer_pixel_low(Tile_Layer_Index layer, Uint8 x, Uint8 y, vec2 value)
{
    update_render_grid_pixel_low(renderer->tile_grid_layers[layer], x, y, value);
}

void update_tile_layer_pixel_high(Tile_Layer_Index layer, Uint8 x, Uint8 y, vec2 value)
{
    update_render_grid_pixel_high(renderer->tile_grid_layers[layer], x, y, value);
}

void free_game_renderer()
{
    if (renderer != NULL) {

        // Free render grid layers
        free_render_grid(renderer->tile_grid_layers[TILE_LAYER_0]);
        free_render_grid(renderer->tile_grid_layers[TILE_LAYER_1]);

        free(renderer);
    }
}