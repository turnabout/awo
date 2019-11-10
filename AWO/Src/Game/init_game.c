#include <stdio.h>
#include <stdlib.h>
#include <cglm/cglm.h>

#include "conf.h"
#include "Game/Inputs/inputs.h"
#include "Game/_game.h"

void init_transformation_matrices(Game* game, GLuint sprites_shader_program)
{
    // View matrix
    mat4 view = GLM_MAT4_IDENTITY_INIT;

    // glm_translate(view, (vec3) { 200.0f, 0.0f, 0.0f } );
    glm_scale(view, (vec3) { (GLfloat)DEFAULT_TILE_DIMENSION, (GLfloat)DEFAULT_TILE_DIMENSION, 1.0f });

    glUniformMatrix4fv(
        glGetUniformLocation(sprites_shader_program, "view"), 1, GL_FALSE, view[0]
    );

    // Projection matrix
    mat4 projection = GLM_MAT4_IDENTITY_INIT;
    glm_ortho(0.0f, (float)game->window_width, 0.0f, (float)game->window_height, -1.0f, 1.0f, projection);

    glUniformMatrix4fv(
        glGetUniformLocation(sprites_shader_program, "projection"), 1, GL_FALSE, projection[0]
    );
}

Game* init_game(int game_board_width, int game_board_height, int window_width, int window_height)
{
    Game* game = (Game*)malloc(sizeof(Game));

    // Initialize base game components: GLFW, GLAD and game data.
    GLuint palettes_texture = 0;

    if (
        !init_GL(game, window_width, window_height) || 
        !init_game_data(game, &palettes_texture)
    ) {
        printf("Failed to initialize\n");
        return NULL;
    }

    // Set transformation matrices
    mat4 view = GLM_MAT4_IDENTITY_INIT;
    glm_scale(view, (vec3) { (GLfloat)DEFAULT_TILE_DIMENSION, (GLfloat)DEFAULT_TILE_DIMENSION, 1.0f });

    mat4 projection = GLM_MAT4_IDENTITY_INIT;
    glm_ortho(0.0f, (float)game->window_width, 0.0f, (float)game->window_height, -1.0f, 1.0f, projection);

    // Initialize game rendering module
    game->renderer = create_game_renderer(
        game_board_width,
        game_board_height,
        palettes_texture
    );

    update_game_renderer_matrix(game->renderer, projection, "projection");
    update_game_renderer_matrix(game->renderer, view, "view");

    // Initialize input handling modules
    init_keys_state_module(game->window);
    init_mouse_state_module(game->window, &game->window_height);

    // Set game board
    game->board = create_game_board(
        game->tiles_data,
        game->clock,
        game_board_width,
        game_board_height
    );

    fill_game_board_tiles(game->board, Sea, Middle);

    return game;
}