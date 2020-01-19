#include <stdlib.h>

#include "conf.h"
#include "GL_Helpers/gl_helpers.h"
#include "Game/Renderer/Stage_Renderer/_stage_renderer.h"
#include "Game/Data/Palette/game_palette.h"

void init_stage_renderer_grid(
    Stage_Renderer* renderer, 
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
        renderer->shader
    );

    // Initially fill grid with transparent pixels
    fill_render_grid_pixels(
        renderer->grid_layers[grid_index], 
        (vec4) { 
            renderer->empty_frame->raw_top_left[0], 
            renderer->empty_frame->raw_top_left[1], 
            0.0,
            0.0
        }
    );
}

Stage_Renderer* create_stage_renderer(Stage* stage, Game_Data* game_data)
{
    Stage_Renderer* renderer = malloc(sizeof(Stage_Renderer));

    if (renderer == NULL) {
        return NULL;
    }

    renderer->stage = stage;

    // Set textures
    renderer->sprite_sheet_texture = game_data->sprite_sheet;

    renderer->palette_texture = create_game_palette_texture(
        game_data->raw_palette,
        WEATHER_DEFAULT,
        stage->player_armies
    );

    // Set shader
    renderer->shader = create_shader_program(
        VERTEX_SHADER_PATH(GRID_SHADER),
        FRAGMENT_SHADER_PATH(GRID_SHADER)
    );

    if (!renderer->shader) {
        free_stage_renderer(renderer);
        return NULL;
    }

    // Set empty frame used for clearing grids
    Animation* empty_animation;
    gather_tile_data(game_data->tiles, Empty, Default, NULL, &empty_animation);

    renderer->empty_frame = &(empty_animation->frames[0]);

    // Set the grid layers
    // Tile grids
    init_stage_renderer_grid(renderer, stage->width, stage->height, TILE_LAYER_0, 0);
    init_stage_renderer_grid(renderer, stage->width, stage->height, TILE_LAYER_1, 1);

    // Unit grids
    init_stage_renderer_grid(renderer, stage->width, stage->height, UNIT_LAYER, 0);

    // Set shader uniforms
    glUseProgram(renderer->shader);
    glUniform1i(glGetUniformLocation(renderer->shader, "sprite_sheet"), 0);
    glUniform1i(glGetUniformLocation(renderer->shader, "palettes_texture"), 1);
    glUniform1i(glGetUniformLocation(renderer->shader, "tiles_texture"), 2);

    glUniform1f(
        glGetUniformLocation(renderer->shader, "sprite_sheet_width"), 
        (GLfloat)game_data->sprite_sheet_width
    );

    glUniform1f(
        glGetUniformLocation(renderer->shader, "sprite_sheet_height"), 
        (GLfloat)game_data->sprite_sheet_height
    );

    glUniform1f(
        glGetUniformLocation(renderer->shader, "quad_width"), 
        (GLfloat)(stage->width * DEFAULT_ENTITY_SIZE)
    );

    glUniform1f(
        glGetUniformLocation(renderer->shader, "quad_height"), 
        (GLfloat)(stage->height * DEFAULT_ENTITY_SIZE)
    );

    return renderer;
}

void free_stage_renderer(Stage_Renderer* renderer)
{
    if (renderer == NULL) {
        return;
    }

    for (int i = 0; i < STAGE_GRID_LAYER_COUNT; i++) {
        free_render_grid(renderer->grid_layers[i]);
    }

    free(renderer);
}