#include <stdio.h>
#include <stdlib.h>
#include <cglm/cglm.h>

#include "conf.h"
#include "GL_Helpers/gl_helpers.h"
#include "Game/Sprite_Batch/sprite_batch.h"
#include "Game/Inputs/inputs.h"
#include "Game/_game.h"

#include "Game/Data/Palette/palette.h"

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
    glm_ortho(0.0f, (float)game->w, 0.0f, (float)game->h, -1.0f, 1.0f, projection);

    glUniformMatrix4fv(
        glGetUniformLocation(sprites_shader_program, "projection"), 1, GL_FALSE, projection[0]
    );
}

int init_game_sprite_batches(Game* game)
{
    // Create sprite batches
    // 1. Main sprites sprite batch
    GLuint sprites_shader_program, sprite_sheet_texture;
    
    if (
        !(sprites_shader_program = create_shader_program(
            SHADERS_PATH "sprite.vert",
            SHADERS_PATH "sprite.frag"
        )) || 
        !(sprite_sheet_texture = create_texture_object(SPRITE_SHEET_PATH))
        ) {
        return 0;
    }

    game->sprite_batches[SPRITES_SPRITE_BATCH] = create_sprite_batch(
        sprites_shader_program,
        sprite_sheet_texture,
        game->palette_texture,
        MAX_SPRITE_BATCH_ELEMENTS
    );

    // Uniforms
    glUseProgram(sprites_shader_program);
    glUniform1i(glGetUniformLocation(sprites_shader_program, "sprite_sheet"), 0);
    glUniform1i(glGetUniformLocation(sprites_shader_program, "palettes_texture"), 1);
    init_transformation_matrices(game, sprites_shader_program);

    // Renderer
    GLuint tiles_renderer_shader = create_shader_program(
        SHADERS_PATH "tiles.vert", 
        SHADERS_PATH "tiles.frag"
    );

    game->tiles_renderer = create_renderer(
        sprite_sheet_texture,
        game->palette_texture,
        tiles_renderer_shader,
        DEFAULT_GAME_BOARD_WIDTH,
        DEFAULT_GAME_BOARD_HEIGHT
    );

    init_transformation_matrices(game, tiles_renderer_shader);

    return 1;
}

void glfw_error_cb(int err_int, const char* err_str)
{
    printf("GLFW Error: %s\n", err_str);
}

int init_glfw(Game* game)
{
    // Initialize GLFW
    glfwSetErrorCallback(glfw_error_cb);
    glfwInit();

    // Get GLFW window
    GLFWwindow* window = glfwCreateWindow(
        DEFAULT_WINDOW_WIDTH, 
        DEFAULT_WINDOW_HEIGHT, 
        DEFAULT_WINDOW_TITLE, 
        NULL, 
        NULL
    );

    if (window == NULL) {
        printf("Failed to create GLFW window\n");
        return 0;
    }

    glfwMakeContextCurrent(window);
    game->window = window;

    return 1;
}

int set_GL_options(Game* game)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Set viewport
    glfwGetWindowSize(game->window, &game->w, &game->h);
    glViewport(0, 0, game->w, game->h);

    // Set initial window position
    GLFWmonitor* primary = glfwGetPrimaryMonitor();

    int monitor_x, monitor_y, monitor_w, monitor_h;
    glfwGetMonitorWorkarea(primary, &monitor_x, &monitor_y, &monitor_w, &monitor_h);

    glfwSetWindowPos(
        game->window,
        monitor_x + ((monitor_w / 2) - (game->w / 2)),
        monitor_y + ((monitor_h / 2) - (game->h / 2))
    );

    // Set other options
    glClearColor(
        (float)GAME_CLEAR_COLOR_R / 255.0f, 
        (float)GAME_CLEAR_COLOR_G / 255.0f, 
        (float)GAME_CLEAR_COLOR_B / 255.0f, 
        (float)GAME_CLEAR_COLOR_A / 255.0f
    );

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return 1;
}

Game* init_game()
{
    Game* game = (Game*)malloc(sizeof(Game));

    // Initialize game components: GLFW, GLAD, game data and sprite batches.
    if (
        !init_glfw(game) || 
        !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) ||
        !set_GL_options(game) ||
        !init_game_data(game) ||
        !init_game_sprite_batches(game)
    ) {
        printf("Failed to initialize\n");
        return NULL;
    }

    // Initialize input handling
    init_keys_state_module(game->window);
    init_mouse_state_module(game->window, &game->h);

    // Set game board
    game->board = create_game_board(
        game->tiles_data,
        game->clock,
        DEFAULT_GAME_BOARD_WIDTH,
        DEFAULT_GAME_BOARD_HEIGHT
    );

    fill_game_board_tiles(game->board, Sea, Middle);

    return game;
}