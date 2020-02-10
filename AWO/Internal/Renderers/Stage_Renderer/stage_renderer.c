#include <stdlib.h>

#include "Config/config.h"
#include "GL_Helpers/gl_helpers.h"
#include "Renderers/Stage_Renderer/_stage_renderer.h"

void add_render_grids_stage_tile_pixel_data(
    Stage_Renderer* renderer, 
    Stage_Tile stage_tile,
    Uint8 x,
    Uint8 y,
    Tile_Data* tile_data
)
{
    if (is_tile_type_neutral(stage_tile.type)) {

        // Get neutral tile's frames
        Animation* tile_anim;
        gather_tile_data(tile_data, stage_tile.type, stage_tile.variation, NULL, &tile_anim);

        // Update the render grid(s) pixel for this tile
        update_render_grid_pixel_low(
            renderer->grid_layers[TILE_LAYER_0],
            x,
            y,
            (vec2) {
                tile_anim->frames[0].raw_top_left[0],
                tile_anim->frames[0].raw_top_left[1]
            }
        );
    } else {
    }
}

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
        renderer->grids_shader_program
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

Stage_Renderer* create_stage_renderer(
    Stage* stage, 
    GLuint palette, 
    GLuint sprite_sheet, 
    Game_Data* game_data
)
{
    Stage_Renderer* renderer = malloc(sizeof(Stage_Renderer));

    if (renderer == NULL) {
        return NULL;
    }

    renderer->stage = stage;

    // Set textures
    renderer->sprite_sheet_texture = sprite_sheet;
    renderer->palette_texture = palette;

    // Set shader
    renderer->grids_shader_program = create_shader_program(
        VERTEX_SHADER_PATH(GRID_SHADER),
        FRAGMENT_SHADER_PATH(GRID_SHADER)
    );

    if (!renderer->grids_shader_program) {
        free_stage_renderer(renderer);
        return NULL;
    }

    // Set empty frame
    Animation* empty_anim;
    gather_tile_data(game_data->tile, Empty, Default, NULL, &empty_anim);
    renderer->empty_frame = &empty_anim->frames[0];

    // Set the grid layers
    // Tile grids
    init_stage_renderer_grid(renderer, stage->width, stage->height, TILE_LAYER_0, 0);
    init_stage_renderer_grid(renderer, stage->width, stage->height, TILE_LAYER_1, 1);

    // Fill tile grids with the stage's tiles initial data
    for (Uint8 y = 0; y < renderer->stage->height; y++) {
        for (Uint8 x = 0; x < renderer->stage->width; x++) {
            add_render_grids_stage_tile_pixel_data(
                renderer, 
                renderer->stage->tiles_grid[y][x],
                x,
                y,
                game_data->tile
            );
        }
    }

    // Unit grids
    init_stage_renderer_grid(renderer, stage->width, stage->height, UNIT_LAYER, 0);

    // Set shader uniforms
    glUseProgram(renderer->grids_shader_program);
    glUniform1i(glGetUniformLocation(renderer->grids_shader_program, "sprite_sheet"), 0);
    glUniform1i(glGetUniformLocation(renderer->grids_shader_program, "palettes_texture"), 1);
    glUniform1i(glGetUniformLocation(renderer->grids_shader_program, "tiles_texture"), 2);

    // Sprite sheet dimensions
    int ss_width, ss_height;
    get_sprite_sheet_dimensions(game_data->sprite_sheet, &ss_width, &ss_height);

    glUniform1f(glGetUniformLocation(renderer->grids_shader_program, "sprite_sheet_width"), (GLfloat)ss_width);
    glUniform1f(glGetUniformLocation(renderer->grids_shader_program, "sprite_sheet_height"), (GLfloat)ss_height);

    // Quad dimensions
    glUniform1f(
        glGetUniformLocation(renderer->grids_shader_program, "quad_width"), 
        (GLfloat)(stage->width * DEFAULT_ENTITY_SIZE)
    );

    glUniform1f(
        glGetUniformLocation(renderer->grids_shader_program, "quad_height"), 
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