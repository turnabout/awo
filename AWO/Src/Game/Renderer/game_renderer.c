#include <stdlib.h>

#include "types.h"
#include "conf.h"
#include "GL_Helpers/gl_helpers.h"
#include "Game/Renderer/game_renderer.h"
#include "Game/Renderer/Render_Grid/render_grid.h"
#include "Game/Renderer/Sprite_Batch/sprite_batch.h"
#include "Game/Data/Palette/game_palette.h"

static Game_Renderer* renderer;

struct Game_Renderer {

    // Dimensions of the raw sprite sheet
    int sprite_sheet_width, sprite_sheet_height;

    // Basic shader program for rendering any sprite.
    GLuint sprites_shader_program;

    // Shader program for rendering tile layers.
    GLuint tiles_shader_program;

    // Texture containing the game's raw sprite sheet.
    GLuint sprite_sheet_texture;

    // Texture containing palettes.
    GLuint game_palette_texture;

    // Reference to the empty tile frame, used to "clear" render grid tiles.
    Animation* empty_tile_frame;

    // Layers of tile grids used to render tiles.
    Render_Grid* tile_grid_layers[TILE_LAYER_TYPE_COUNT];

    // Sprite batch used to draw UI elements.
    Sprite_Batch* sprite_batch;

    // Whether the sprite batch's 'spritebatch_begin' function was previously called.
    Bool sprite_batch_started;
};

Bool init_game_renderer_shader_programs()
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
        return FALSE;
    }

    return TRUE;
}

void init_game_renderer_uniforms(int tiles_layer_width, int tiles_layer_height)
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
        (GLfloat)(tiles_layer_width * DEFAULT_TILE_SIZE)
    );

    glUniform1f(
        glGetUniformLocation(renderer->tiles_shader_program, "quad_height"), 
        (GLfloat)(tiles_layer_height * DEFAULT_TILE_SIZE)
    );

}

void init_game_renderer(
    int render_grid_width, 
    int render_grid_height, 
    GLuint game_palette_texture,
    Tiles_Data* tiles_data
)
{
    renderer = malloc(sizeof(Game_Renderer));

    if (!init_game_renderer_shader_programs()) {
        free(renderer);
        return;
    }

    // Set textures
    renderer->sprite_sheet_texture = create_texture_object(
        SPRITE_SHEET_PATH, 
        &renderer->sprite_sheet_width, 
        &renderer->sprite_sheet_height
    );

    renderer->game_palette_texture = game_palette_texture;
    init_game_renderer_uniforms(render_grid_width, render_grid_height);

    // Set sprite batch
    renderer->sprite_batch = create_sprite_batch(
        renderer->sprites_shader_program,
        renderer->sprite_sheet_texture,
        game_palette_texture,
        MAX_SPRITE_BATCH_ELEMENTS
    );

    // Set render grids - set empty tile frames used to initially fill every layer
    gather_tile_data(tiles_data, Empty, Default, NULL, NULL, &renderer->empty_tile_frame);
    Uint8 offset_y = 0;

    for (int i = 0; i < TILE_LAYER_TYPE_COUNT; i++) {
        renderer->tile_grid_layers[i] = create_render_grid(
            render_grid_width, 
            render_grid_height, 
            offset_y++,
            renderer->tiles_shader_program
        );
        
        fill_render_grid_pixels(
            renderer->tile_grid_layers[i], 
            (vec4) { 
                renderer->empty_tile_frame->frames[0].raw_top_left[0], 
                renderer->empty_tile_frame->frames[0].raw_top_left[1], 
                0.0,
                0.0
            }
        );
    }
}

void update_game_renderer_matrix(mat4 matrix, const char* matrix_str)
{
    mat4 test = GLM_MAT4_IDENTITY_INIT;

    // Refresh position
    glm_translate(
        test,
        (vec3) { (float)560, (float)320, 0.0f }
    );

    // Refresh zoom
    glm_scale(
        test,
        (vec3) { 32.0f, 32.0f, 1.0f }
    );

    // Update sprites shader's given matrix
    glUseProgram(renderer->sprites_shader_program);

    glUniformMatrix4fv(
        glGetUniformLocation(renderer->sprites_shader_program, matrix_str), 
        1, 
        GL_FALSE, 
        matrix[0]
    );

    glUniformMatrix4fv(
        glGetUniformLocation(renderer->sprites_shader_program, "view"), 
        1, 
        GL_FALSE, 
        test[0]
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

void update_tile_layer_pixel(
    Tile_Layer_Index layer,
    Uint8 x,
    Uint8 y,
    vec4 value
)
{
    update_render_grid_pixel(renderer->tile_grid_layers[layer], x, y, value);
}

void update_tile_layer_pixel_low(
    Tile_Layer_Index layer,
    Uint8 x,
    Uint8 y,
    vec2 value
)
{
    update_render_grid_pixel_low(renderer->tile_grid_layers[layer], x, y, value);
}

void update_tile_layer_pixel_high(
    Tile_Layer_Index layer,
    Uint8 x,
    Uint8 y,
    vec2 value
)
{
    update_render_grid_pixel_high(renderer->tile_grid_layers[layer], x, y, value);
}

void batch_sprite(
    vec2 dst, 
    Frame* frame_data, 
    GLfloat palette_index
)
{
    // Begin the sprite batch if it hasn't already begun
    if (!renderer->sprite_batch_started) {
        begin_sprite_batch(renderer->sprite_batch);
        renderer->sprite_batch_started = TRUE;
    }

    add_to_sprite_batch(renderer->sprite_batch, dst, frame_data, palette_index);
}

void render_game_renderer()
{
    /*
    // Render the tile render grids
    glUseProgram(renderer->tiles_shader_program);

    glActiveTexture(GL_TEXTURE0); 
    glBindTexture(GL_TEXTURE_2D, renderer->sprite_sheet_texture);

    glActiveTexture(GL_TEXTURE1); 
    glBindTexture(GL_TEXTURE_2D, renderer->game_palette_texture);

    render_r_grid(renderer->tile_grid_layers[TILE_LAYER_0]);
    render_r_grid(renderer->tile_grid_layers[TILE_LAYER_1]);
    */
    // Render sprite batch contents
    glUseProgram(renderer->sprites_shader_program);

    glActiveTexture(GL_TEXTURE0); 
    glBindTexture(GL_TEXTURE_2D, renderer->sprite_sheet_texture);

    glActiveTexture(GL_TEXTURE1); 
    glBindTexture(GL_TEXTURE_2D, renderer->game_palette_texture);

    end_sprite_batch(renderer->sprite_batch);
    renderer->sprite_batch_started = FALSE;
}

void free_game_renderer()
{
    if (renderer != NULL) {

        // Free render grid layers
        free_render_grid(renderer->tile_grid_layers[TILE_LAYER_0]);
        free_render_grid(renderer->tile_grid_layers[TILE_LAYER_1]);

        free_sprite_batch(renderer->sprite_batch);

        free(renderer);
    }
}