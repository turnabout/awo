#include "Game/Renderer/_game_renderer.h"

void _free_game_renderer(Game_Renderer* renderer)
{
    if (renderer != NULL) {

        // Free render grid layers
        free_render_grid(renderer->tile_grid_layers[TILE_LAYER_0]);
        free_render_grid(renderer->tile_grid_layers[TILE_LAYER_1]);

        free(renderer);
    }
}
