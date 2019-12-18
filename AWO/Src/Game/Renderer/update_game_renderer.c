#include "Game/Renderer/_game_renderer.h"

void update_game_renderer_matrix(Game_Renderer* renderer, mat4 matrix, const char* matrix_str)
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

void clear_tile_layers_pixel(Game_Renderer* renderer, Uint8 x, Uint8 y)
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

void update_tile_layer_pixel(Game_Renderer* renderer, Tile_Layer_Index layer, Uint8 x, Uint8 y, vec4 value)
{
    update_render_grid_pixel(renderer->tile_grid_layers[layer], x, y, value);
}

void update_tile_layer_pixel_low(Game_Renderer* renderer, Tile_Layer_Index layer, Uint8 x, Uint8 y, vec2 value)
{
    update_render_grid_pixel_low(renderer->tile_grid_layers[layer], x, y, value);
}

void update_tile_layer_pixel_high(Game_Renderer* renderer, Tile_Layer_Index layer, Uint8 x, Uint8 y, vec2 value)
{
    update_render_grid_pixel_high(renderer->tile_grid_layers[layer], x, y, value);
}

void free_game_renderer(Game_Renderer* renderer)
{
    if (renderer != NULL) {

        // Free render grid layers
        free_render_grid(renderer->tile_grid_layers[TILE_LAYER_0]);
        free_render_grid(renderer->tile_grid_layers[TILE_LAYER_1]);

        // Free extras renderer

        free(renderer);
    }
}
