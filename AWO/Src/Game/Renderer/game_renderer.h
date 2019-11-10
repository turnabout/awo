#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef struct Game_Renderer Game_Renderer;

typedef enum Tile_Layer_Type {
    TILE_LAYER_0,
    TILE_LAYER_1,
} Tile_Layer_Type;

#define TILE_LAYER_TYPE_COUNT TILE_LAYER_1 + 1

Game_Renderer* create_game_renderer(
    int tile_layers_width, 
    int tile_layers_height, 
    GLuint palettes_texture
);

void free_game_renderer(Game_Renderer* renderer);
