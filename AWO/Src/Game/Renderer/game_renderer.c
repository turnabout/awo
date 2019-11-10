#include <stdlib.h>
#include <cglm/cglm.h>

#include "conf.h"
#include "GL_Helpers/gl_helpers.h"
#include "Game/Renderer/game_renderer.h"
#include "Game/Renderer/Tiles_Layer/tiles_layer.h"
#include "Game/Renderer/Sprite_Batch/sprite_batch.h"

struct Game_Renderer {

    // Basic shader program for rendering any sprite.
    GLuint sprites_shader_program;

    // Shader program for rendering tile layers.
    GLuint tiles_shader_program;

    // Texture containing the game's raw sprite sheet.
    GLuint sprite_sheet_texture;

    // Texture containing palettes.
    GLuint palettes_texture;

    // Dimensions of the raw sprite sheet
    int sprite_sheet_width, sprite_sheet_height;

    // Tiles layers, used to render tiles in single draw calls.
    Tiles_Layer* tiles_layers[TILE_LAYER_TYPE_COUNT];

    // VAO used by tiles layers
    GLuint tiles_layers_VAO;
};

int init_game_renderer_shader_programs(Game_Renderer* renderer)
{
    renderer->sprites_shader_program = create_shader_program(
        SHADERS_PATH "sprite.vert",
        SHADERS_PATH "sprite.frag"
    );

    renderer->tiles_shader_program = create_shader_program(
        SHADERS_PATH "tiles.vert",
        SHADERS_PATH "tiles.frag"
    );

    if (!renderer->sprites_shader_program || !renderer->tiles_shader_program) {
        return 0;
    }

    return 1;
}

void init_game_renderer_uniforms(Game_Renderer* renderer)
{
    // Sprites shader
    glUseProgram(renderer->sprites_shader_program);
    glUniform1i(glGetUniformLocation(renderer->sprites_shader_program, "sprite_sheet"), 0);
    glUniform1i(glGetUniformLocation(renderer->sprites_shader_program, "palettes_texture"), 1);

    // Tiles shader
    glUseProgram(renderer->tiles_shader_program);
    glUniform1i(glGetUniformLocation(renderer->sprites_shader_program, "sprite_sheet"), 0);
    glUniform1i(glGetUniformLocation(renderer->sprites_shader_program, "palettes_texture"), 1);
}

void init_tiles_layers(Game_Renderer* renderer, int tiles_layer_width, int tiles_layer_height)
{
    renderer->tiles_layers_VAO = get_tiles_layers_VAO(tiles_layer_width, tiles_layer_height);

    for (int i = 0; i < TILE_LAYER_TYPE_COUNT; i++) {
        renderer->tiles_layers[i] = create_tiles_layer(tiles_layer_width, tiles_layer_height);
    }
}

Game_Renderer* create_game_renderer(
    int tiles_layer_width, 
    int tiles_layer_height, 
    GLuint palettes_texture
)
{
    Game_Renderer* renderer = (Game_Renderer*)malloc(sizeof(Game_Renderer));

    if (!init_game_renderer_shader_programs(renderer)) {
        free_game_renderer(renderer);
        return NULL;
    }

    // Set sprite sheet texture
    renderer->sprite_sheet_texture = create_texture_object(
        SPRITE_SHEET_PATH, 
        &renderer->sprite_sheet_width, 
        &renderer->sprite_sheet_height
    );

    renderer->palettes_texture = palettes_texture;

    // Set sprite batches
    /*
    game->sprite_batches[SPRITES_SPRITE_BATCH] = create_sprite_batch(
        sprites_shader_program,
        sprite_sheet_texture,
        game->palette_texture,
        MAX_SPRITE_BATCH_ELEMENTS
    );
    */

    // Set tiles layers
    init_tiles_layers(renderer, tiles_layer_width, tiles_layer_height);

    return renderer;
}

void free_game_renderer(Game_Renderer* renderer)
{
    if (renderer != NULL) {

        // Free tiles layers
        for (int i = 0; i < TILE_LAYER_TYPE_COUNT; i++) {
            free_tiles_layer(renderer->tiles_layers[i]);
        }

        free(renderer);
    }
}