#include <stdlib.h>

#include "conf.h"
#include "GL_Helpers/gl_helpers.h"
#include "Game/Renderer/game_renderer.h"
#include "Game/Renderer/Tiles_Layer/tiles_layer.h"
#include "Game/Renderer/Sprite_Batch/sprite_batch.h"
#include "Game/Data/Palette/palette.h"

static Game_Renderer* renderer;

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

int init_game_renderer_shader_programs()
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

void init_game_renderer_uniforms(
    int tiles_layer_width, 
    int tiles_layer_height
)
{
    // Sprites shader
    glUseProgram(renderer->sprites_shader_program);
    glUniform1i(glGetUniformLocation(renderer->sprites_shader_program, "sprite_sheet"), 0);
    glUniform1i(glGetUniformLocation(renderer->sprites_shader_program, "palettes_texture"), 1);

    // Tiles shader
    glUseProgram(renderer->tiles_shader_program);
    glUniform1i(glGetUniformLocation(renderer->tiles_shader_program, "sprite_sheet"), 0);
    glUniform1i(glGetUniformLocation(renderer->tiles_shader_program, "palettes_texture"), 1);
    glUniform1i(glGetUniformLocation(renderer->tiles_shader_program, "tiles_texture"), 2);

    glUniform1f(
        glGetUniformLocation(renderer->tiles_shader_program, "sprite_sheet_width"), 
        (GLfloat)renderer->sprite_sheet_width
    );

    glUniform1f(
        glGetUniformLocation(renderer->tiles_shader_program, "sprite_sheet_height"), 
        (GLfloat)renderer->sprite_sheet_height
    );

    glUniform1f(
        glGetUniformLocation(renderer->tiles_shader_program, "quad_width"), 
        (GLfloat)(tiles_layer_width * DEFAULT_TILE_DIMENSION)
    );

    glUniform1f(
        glGetUniformLocation(renderer->tiles_shader_program, "quad_height"), 
        (GLfloat)(tiles_layer_height * DEFAULT_TILE_DIMENSION)
    );

}

void init_game_renderer(
    int tiles_layer_width, 
    int tiles_layer_height, 
    GLuint palettes_texture,
    Tiles_Data* tiles_data
)
{
    renderer = (Game_Renderer*)malloc(sizeof(Game_Renderer));

    if (!init_game_renderer_shader_programs(renderer)) {
        free_game_renderer(renderer);
        return;
    }

    // Set textures
    renderer->sprite_sheet_texture = create_texture_object(
        SPRITE_SHEET_PATH, 
        &renderer->sprite_sheet_width, 
        &renderer->sprite_sheet_height
    );
    renderer->palettes_texture = palettes_texture;
    init_game_renderer_uniforms(tiles_layer_width, tiles_layer_height);

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
    renderer->tiles_layers_VAO = get_tiles_layers_VAO(tiles_layer_width, tiles_layer_height);

    // Get empty tile frames used to initially fill every layer
    Animation* empty_tile_frames;
    gather_tile_data(tiles_data, Empty, Default, NULL, NULL, &empty_tile_frames);

    for (int i = 0; i < TILE_LAYER_TYPE_COUNT; i++) {
        renderer->tiles_layers[i] = create_tiles_layer(tiles_layer_width, tiles_layer_height);
        
        fill_tiles_layer_pixels(
            renderer->tiles_layers[i], 
            (vec4) { 
                empty_tile_frames->frames[0].raw_top_left[0], 
                empty_tile_frames->frames[0].raw_top_left[1], 
                get_active_tile_palette_index(0), 
                0.0 
            }
        );
    }

    // Test: initially fill layer 0 with plains
    /*
    fill_tiles_layer_pixels(
        renderer->tiles_layers[TILE_LAYER_0], 
        (vec4) { 
            0.0f, 
            96.0f, 
            get_active_tile_palette_index(1), 
            0.0f
        }
    );
    */
}

void update_game_renderer_matrix(mat4 matrix, const char* matrix_str)
{
    // Update sprites shader's given matrix
    glUseProgram(renderer->sprites_shader_program);

    glUniformMatrix4fv(
        glGetUniformLocation(renderer->sprites_shader_program, matrix_str), 
        1, 
        GL_FALSE, 
        matrix[0]
    );

    // Update tiles shader's given matrix
    glUseProgram(renderer->tiles_shader_program);

    glUniformMatrix4fv(
        glGetUniformLocation(renderer->tiles_shader_program, matrix_str), 
        1, 
        GL_FALSE, 
        matrix[0]
    );
}

void update_renderer_tiles_layer_pixel(
    Tile_Layer_Index layer,
    GLuint x,
    GLuint y,
    vec4 value
)
{
    update_tiles_layer_pixel(renderer->tiles_layers[layer], x, y, value);
}

void update_renderer_tiles_layer_pixel_low(
    Tile_Layer_Index layer,
    GLuint x,
    GLuint y,
    vec2 value
)
{
    update_tiles_layer_pixel_low(renderer->tiles_layers[layer], x, y, value);
}

void render_tiles_layers()
{
    // Render tiles layers
    glUseProgram(renderer->tiles_shader_program);
    glBindVertexArray(renderer->tiles_layers_VAO);

    glActiveTexture(GL_TEXTURE0); 
    glBindTexture(GL_TEXTURE_2D, renderer->sprite_sheet_texture);

    glActiveTexture(GL_TEXTURE1); 
    glBindTexture(GL_TEXTURE_2D, renderer->palettes_texture);

    for (int i = 0; i < TILE_LAYER_TYPE_COUNT; i++) {
        render_tiles_layer(renderer->tiles_layers[i]);
    }
}

void bind_tile_layer_texture(Tile_Layer_Index tile_layer)
{
    bind_tile_texture(renderer->tiles_layers[tile_layer]);
}

void free_game_renderer()
{
    if (renderer != NULL) {

        // Free tiles layers
        for (int i = 0; i < TILE_LAYER_TYPE_COUNT; i++) {
            free_tiles_layer(renderer->tiles_layers[i]);
        }

        free(renderer);
    }
}