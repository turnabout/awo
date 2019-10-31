#include <stdio.h>
#include <stdlib.h>
#include <cglm/cglm.h>

#include "conf.h"
#include "GL_Helpers/gl_helpers.h"
#include "Game/Sprite_Batch/sprite_batch.h"
#include "Game/Inputs/inputs.h"
#include "Game/_game.h"

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

    // Set main projection matrix uniform
    mat4 main_projection;
    glm_ortho(0.0f, (float)game->w, 0.0f, (float)game->h, -1.0f, 1.0f, main_projection);

    // Set uniforms for main sprites' sprite batch
    glUseProgram(sprites_shader_program);

    // Projection matrix
    glUniformMatrix4fv(
        glGetUniformLocation(sprites_shader_program, "projection"), 1, GL_FALSE, main_projection[0]
    );

    // Textures
    glUniform1i(glGetUniformLocation(sprites_shader_program, "sprite_sheet"), 0);
    glUniform1i(glGetUniformLocation(sprites_shader_program, "color_table"), 1);

    glUseProgram(0);

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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

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

Game* init_game()
{
    Game* game = (Game*)malloc(sizeof(Game));

    // GLFW | GLAD
    if (!init_glfw(game) || !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize\n");
        return NULL;
    }

    glfwGetWindowSize(game->window, &game->w, &game->h);
    glViewport(0, 0, game->w, game->h);

    // Load the game's data
    if (!init_game_data(game)) {
        return NULL;
    }

    // Set the game's sprite batches used for rendering
    if (!init_game_sprite_batches(game)) {
        return NULL;
    }

    // Initialize input handling
    init_keys_state_module(game->window);
    init_mouse_state_module(game->window, &game->h);

    // Set some other options
    glClearColor(
        (float)DEFAULT_GAME_BG_R / 255.0f, 
        (float)DEFAULT_GAME_BG_G / 255.0f, 
        (float)DEFAULT_GAME_BG_B / 255.0f, 
        (float)DEFAULT_GAME_BG_A / 255.0f
    );

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return game;
}