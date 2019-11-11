#include <stdio.h>
#include <stdlib.h>
#include <cglm/cglm.h>

#include "conf.h"
#include "Game/Inputs/inputs.h"
#include "Game/_game.h"

Game* init_game(int game_board_width, int game_board_height, int window_width, int window_height)
{
    Game* game = (Game*)malloc(sizeof(Game));

    // Initialize base game components: GLFW, GLAD and game data.
    if (
        !init_GL(game, window_width, window_height) || 
        !init_game_data(game)
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
        game->palettes_texture,
        game->tiles_data
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