#include "Game/Renderer/_game_renderer.h"

void clear_tile_layers_pixel(Game_Renderer* renderer, Uint8 x, Uint8 y)
{
    for (int i = 0; i < TILE_LAYER_COUNT; i++) {
        update_render_grid_pixel_low(
            renderer->grid_layers[i],
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
    update_render_grid_pixel(renderer->grid_layers[layer], x, y, value);
}

void update_tile_layer_pixel_low(Game_Renderer* renderer, Tile_Layer_Index layer, Uint8 x, Uint8 y, vec2 value)
{
    update_render_grid_pixel_low(renderer->grid_layers[layer], x, y, value);
}

void update_tile_layer_pixel_high(Game_Renderer* renderer, Tile_Layer_Index layer, Uint8 x, Uint8 y, vec2 value)
{
    update_render_grid_pixel_high(renderer->grid_layers[layer], x, y, value);
}

void free_game_renderer(Game_Renderer* renderer)
{
    if (renderer != NULL) {

        // Free render grid layers
        free_render_grid(renderer->grid_layers[TILE_LAYER_0]);
        free_render_grid(renderer->grid_layers[TILE_LAYER_1]);

        // Free extras renderer
        free_extras_renderer(renderer->extras_renderer);

        free(renderer);
    }

    renderer = NULL;
}
