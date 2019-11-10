#include <stdlib.h>
#include <cglm/cglm.h>

#include "conf.h"
#include "GL_Helpers/gl_helpers.h"
#include "Game/Renderer/game_renderer.h"

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

Game_Renderer* create_game_renderer(
    int tile_layers_width, 
    int tile_layers_height, 
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
    // Create tiles renderer
    /*
    renderer->tiles_renderer = create_tiles_renderer(
        DEFAULT_GAME_BOARD_WIDTH,
        DEFAULT_GAME_BOARD_HEIGHT,
        sprite_sheet_texture,
        0,
        0
    );
    */

    return renderer;
}

void free_game_renderer(Game_Renderer* renderer)
{
    // TODO
    free(renderer);
}