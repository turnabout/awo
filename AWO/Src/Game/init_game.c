#include <stdio.h>
#include <stdlib.h>
#include <cglm/cglm.h>

#include "conf.h"
#include "GL_Helpers/gl_helpers.h"
#include "Game/Sprite_Batch/sprite_batch.h"
#include "Game/Inputs/inputs.h"
#include "Game/_game.h"

GLubyte make_palette_texture__test()
{
    #define palette_tex_width 256
    #define palette_text_height 1
    GLubyte checkImage[palette_text_height][palette_tex_width][4];

    for (int i = 0; i < palette_tex_width; i++) {
        checkImage[0][i][0] = (GLubyte)i;
        checkImage[0][i][1] = (GLubyte)0;
        checkImage[0][i][2] = (GLubyte)0;
        checkImage[0][i][3] = (GLubyte)255;
    }

    // glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, palette_tex_width, palette_text_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);

    return texture;
}

int init_game_sprite_batches(Game* game, GLint* ss_width, GLint* ss_height)
{
    // Create sprite batches
    // 1. Main sprites sprite batch
    GLuint sprites_shader_program, sprite_sheet_texture, palette_texture;
    
    if (
        !(sprites_shader_program = create_shader_program(
            SHADERS_PATH "sprite.vert",
            SHADERS_PATH "sprite.frag"
        )) || 
        !(sprite_sheet_texture = create_texture_object(SPRITE_SHEET_PATH, ss_width, ss_height))
        ) {
        return 0;
    }

    palette_texture = make_palette_texture__test();

    game->sprite_batches[SPRITES_SPRITE_BATCH] = create_sprite_batch(
        sprites_shader_program,
        sprite_sheet_texture,
        palette_texture,
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

    // Set the game's sprite batches used for rendering
    GLint sprite_sheet_w, sprite_sheet_h;
    if (!init_game_sprite_batches(game, &sprite_sheet_w, &sprite_sheet_h)) {
        return NULL;
    }

    // Load the game's data
    if (!init_game_data(game, sprite_sheet_w, sprite_sheet_h)) {
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