#include <stdio.h>
#include <stdlib.h>

#include "conf.h"
#include "GL_Helpers/gl_helpers.h"
#include "Game/_game.h"

Game* init_game()
{
    Game* game = (Game*)malloc(sizeof(game));

    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Get GLFW window
    game->window = glfwCreateWindow(
        DEFAULT_WINDOW_WIDTH, 
        DEFAULT_WINDOW_HEIGHT, 
        DEFAULT_WINDOW_TITLE, 
        NULL, 
        NULL
    );

    if (game->window == NULL) {
        printf("Failed to create GLFW window\n");
        return NULL;
    }

    glfwMakeContextCurrent(game->window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        return NULL;
    }

    glViewport(0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);

    // Create shader_program programs
    game->shader_program = create_shader_program(SHADERS_PATH "sprite.vert", SHADERS_PATH "sprite.frag");

    if (game->shader_program == 0) {
        return NULL;
    }

    // Load sprite sheet
    game->sprite_sheet = create_texture_object(SPRITE_SHEET_PATH);

    if (game->sprite_sheet == 0) {
        return NULL;
    }

    glUseProgram(game->shader_program);
    glUniform1i(glGetUniformLocation(game->shader_program, "sprite_sheet"), 0);

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