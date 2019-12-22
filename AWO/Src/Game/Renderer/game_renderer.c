#include <stdlib.h>

#include "GL_Helpers/gl_helpers.h"
#include "Game/Renderer/_game_renderer.h"

#include "Game/Data/Palette/game_palette.h"

Bool init_game_renderer_shader_programs(Game_Renderer* renderer)
{
    renderer->grid_shader = create_shader_program(
        VERTEX_SHADER_PATH(GRID_SHADER),
        FRAGMENT_SHADER_PATH(GRID_SHADER)
    );

    if (!renderer->grid_shader) {
        return FALSE;
    }

    return TRUE;
}

void init_grid_shader_uniforms(
    Game_Renderer* renderer,
    int grid_width, 
    int grid_height,
    int ss_width,
    int ss_height
)
{
    glUseProgram(renderer->grid_shader);
    glUniform1i(glGetUniformLocation(renderer->grid_shader, "sprite_sheet"), 0);
    glUniform1i(glGetUniformLocation(renderer->grid_shader, "palettes_texture"), 1);
    glUniform1i(glGetUniformLocation(renderer->grid_shader, "tiles_texture"), 2);

    glUniform1f(
        glGetUniformLocation(renderer->grid_shader, "sprite_sheet_width"), 
        (GLfloat)ss_width
    );

    glUniform1f(
        glGetUniformLocation(renderer->grid_shader, "sprite_sheet_height"), 
        (GLfloat)ss_height
    );

    glUniform1f(
        glGetUniformLocation(renderer->grid_shader, "quad_width"), 
        (GLfloat)(grid_width * DEFAULT_ENTITY_SIZE)
    );

    glUniform1f(
        glGetUniformLocation(renderer->grid_shader, "quad_height"), 
        (GLfloat)(grid_height * DEFAULT_ENTITY_SIZE)
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
    renderer->grid_layers[grid_index] = create_render_grid(
        grid_width, 
        grid_height, 
        y_offset,
        renderer->grid_shader
    );

    // Initially fill grid with empty tile
    fill_render_grid_pixels(
        renderer->grid_layers[grid_index], 
        (vec4) { 
            renderer->empty_tile_frame->frames[0].raw_top_left[0], 
            renderer->empty_tile_frame->frames[0].raw_top_left[1], 
            0.0,
            0.0
        }
    );
}

void init_game_renderer_grids(
    Game_Renderer* renderer, 
    int grid_width, 
    int grid_height, 
    int ss_width, 
    int ss_height
)
{
    // Tile grids
    init_game_renderer_grid(renderer, grid_width, grid_height, TILE_LAYER_0, 0);
    init_game_renderer_grid(renderer, grid_width, grid_height, TILE_LAYER_1, 1);

    // Unit grids
    init_game_renderer_grid(renderer, grid_width, grid_height, UNIT_LAYER, 0);

    // Set uniforms
    init_grid_shader_uniforms(renderer, grid_width, grid_height, ss_width, ss_height);
}

Game_Renderer* create_game_renderer(
    int grid_width, 
    int grid_height, 
    GLuint game_palette_texture,
    Tiles_Data* tiles_data,
    int window_width, 
    int window_height
)
{
    Game_Renderer* renderer = malloc(sizeof(Game_Renderer));

    renderer->game_palette_texture = game_palette_texture;
    gather_tile_data(tiles_data, Empty, Default, NULL, NULL, &renderer->empty_tile_frame);

    // Shaders managed by the game renderer itself
    if (!init_game_renderer_shader_programs(renderer)) {
        free(renderer);
        return NULL;
    }

    // Sprite sheet texture
    int ss_width, ss_height;
    renderer->sprite_sheet_texture = create_texture_object(SPRITE_SHEET_PATH, &ss_width, &ss_height);

    // Render grids
    init_game_renderer_grids(renderer, grid_width, grid_height, ss_width, ss_height);

    // Extras renderer
    renderer->extras_renderer = create_extras_renderer(renderer->sprite_sheet_texture);

    // Projection matrices
    update_game_renderer_projection_matrices(renderer, window_width, window_height);

    return renderer;
}
