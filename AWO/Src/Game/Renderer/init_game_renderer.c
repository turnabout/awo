#include <stdlib.h>

#include "GL_Helpers/gl_helpers.h"
#include "Game/Renderer/_game_renderer.h"

Bool init_game_renderer_shader_programs(Game_Renderer* renderer)
{
    renderer->tiles_shader_program = create_shader_program(
        VERTEX_SHADER_PATH(TILES_SHADER),
        FRAGMENT_SHADER_PATH(TILES_SHADER)
    );

    if (!renderer->tiles_shader_program) {
        return FALSE;
    }

    return TRUE;
}

void init_game_renderer_uniforms(
    Game_Renderer* renderer, 
    int grid_width, 
    int grid_height,
    int ss_width,
    int ss_height
)
{
    // Initialize tiles shader uniform
    glUseProgram(renderer->tiles_shader_program);
    glUniform1i(glGetUniformLocation(renderer->tiles_shader_program, "sprite_sheet"), 0);
    glUniform1i(glGetUniformLocation(renderer->tiles_shader_program, "palettes_texture"), 1);
    glUniform1i(glGetUniformLocation(renderer->tiles_shader_program, "tiles_texture"), 2);

    glUniform1f(
        glGetUniformLocation(renderer->tiles_shader_program, "sprite_sheet_width"), 
        (GLfloat)ss_width
    );

    glUniform1f(
        glGetUniformLocation(renderer->tiles_shader_program, "sprite_sheet_height"), 
        (GLfloat)ss_height
    );

    glUniform1f(
        glGetUniformLocation(renderer->tiles_shader_program, "quad_width"), 
        (GLfloat)(grid_width * DEFAULT_TILE_SIZE)
    );

    glUniform1f(
        glGetUniformLocation(renderer->tiles_shader_program, "quad_height"), 
        (GLfloat)(grid_height * DEFAULT_TILE_SIZE)
    );
}

void init_game_renderer_grid(
    Game_Renderer* renderer, 
    int grid_width, 
    int grid_height,
    int grid_index,
    int y_offset
)
{
    renderer->tile_grid_layers[grid_index] = create_render_grid(
        grid_width, 
        grid_height, 
        y_offset,
        renderer->tiles_shader_program
    );

    // Initially fill grid with empty tile
    fill_render_grid_pixels(
        renderer->tile_grid_layers[grid_index], 
        (vec4) { 
        renderer->empty_tile_frame->frames[0].raw_top_left[0], 
        renderer->empty_tile_frame->frames[0].raw_top_left[1], 
        0.0,
        0.0
        }
    );
}

void init_game_renderer_grids(Game_Renderer* renderer, int grid_width, int grid_height)
{
    // Set tile grids
    init_game_renderer_grid(renderer, grid_width, grid_height, TILE_LAYER_0, 0);
    init_game_renderer_grid(renderer, grid_width, grid_height, TILE_LAYER_1, 1);
}

Game_Renderer* _init_game_renderer(
    int grid_width, 
    int grid_height, 
    GLuint game_palette_texture,
    Tiles_Data* tiles_data
)
{
    Game_Renderer* renderer = malloc(sizeof(Game_Renderer));

    renderer->game_palette_texture = game_palette_texture;
    gather_tile_data(tiles_data, Empty, Default, NULL, NULL, &renderer->empty_tile_frame);

    // Initialize shaders managed by the game renderer itself
    if (!init_game_renderer_shader_programs(renderer)) {
        free(renderer);
        return NULL;
    }

    // Initialize sprite sheet texture
    int ss_width, ss_height;
    renderer->sprite_sheet_texture = create_texture_object(SPRITE_SHEET_PATH, &ss_width, &ss_height);

    // Initialize uniforms for shaders managed by the game renderer
    init_game_renderer_uniforms(renderer, grid_width, grid_height, ss_width, ss_height);

    // Initialize render grids
    init_game_renderer_grids(renderer, grid_width, grid_height);

    // TODO: initialize extras renderer

    return renderer;
}