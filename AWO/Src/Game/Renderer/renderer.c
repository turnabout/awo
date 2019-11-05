#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "conf.h"
#include "GL_Helpers/gl_helpers.h"
#include "Game/Renderer/renderer.h"

struct Renderer {
    GLuint shader;
    GLuint VAO;
    GLuint sprite_sheet_tex;
    GLuint palette_tex;
    GLuint tiles_tex;
};

void init_renderer_buffer(Renderer* renderer)
{
    size_t stride = 4 * sizeof(GLfloat);
    size_t quad_size = 4 * stride;

    // VAO
    glGenVertexArrays(1, &renderer->VAO);
    glBindVertexArray(renderer->VAO);

    // EBO
    GLuint indices[] = {
        0, 1, 2, // First triangle
        3, 0, 2, // Second triangle
    };

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // VBO
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    #define ss_width  628
    #define ss_height 396

    #define left    0
    #define bottom  0
    #define top     ss_height
    #define right   ss_width

    GLfloat quad_vertices[4][4] = {
        // Bottom left
        {
            left, bottom, // Position
            0.0f, 1.0f,   // Texture coordinates
        }, 
        // Top left
        { 
            left, top,  // Position
            0.0f, 0.0f, // Texture coordinates
        }, 
        // Top right
        { 
            right, top, // Position
            1.0f, 0.0f, // Texture coordinates
        }, 
        // Bottom right
        { 
            right, bottom, // Position
            1.0f, 1.0f,    // Texture coordinates
        }, 
    };

    glBufferData(GL_ARRAY_BUFFER, quad_size, quad_vertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void*)(0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
}

void init_tiles_texture(Renderer* renderer)
{
    GLuint tiles_tex_data[DEFAULT_GAME_BOARD_HEIGHT][DEFAULT_GAME_BOARD_WIDTH][4];

    for (int i = 0; i < DEFAULT_GAME_BOARD_WIDTH; i++) {
        tiles_tex_data[0][i][0] = (GLubyte)i;
        tiles_tex_data[0][i][1] = (GLubyte)0;
        tiles_tex_data[0][i][2] = (GLubyte)0;
        tiles_tex_data[0][i][3] = (GLubyte)255;
    }

    glGenTextures(1, &renderer->tiles_tex);
    glBindTexture(GL_TEXTURE_2D, renderer->tiles_tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, DEFAULT_GAME_BOARD_WIDTH, DEFAULT_GAME_BOARD_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, tiles_tex_data);
}

Renderer* create_renderer(GLuint sprite_sheet_tex, GLuint palette_tex, GLuint shader)
{
    Renderer* renderer = (Renderer*)malloc(sizeof(Renderer));

    renderer->shader = shader;
    renderer->sprite_sheet_tex = sprite_sheet_tex;
    renderer->palette_tex = palette_tex;

    glUseProgram(renderer->shader);

    glUniform1i(glGetUniformLocation(renderer->sprite_sheet_tex, "sprite_sheet"), 0);
    glUniform1i(glGetUniformLocation(renderer->palette_tex, "palettes_texture"), 1);
    glUniform1i(glGetUniformLocation(renderer->tiles_tex, "tiles_texture"), 2);

    init_renderer_buffer(renderer);
    init_tiles_texture(renderer);

    return renderer;
}

void render(Renderer* renderer, int x_offset, int y_offset)
{
    glUseProgram(renderer->shader);

    glActiveTexture(GL_TEXTURE0); 
    glBindTexture(GL_TEXTURE_2D, renderer->sprite_sheet_tex);

    glActiveTexture(GL_TEXTURE1); 
    glBindTexture(GL_TEXTURE_2D, renderer->palette_tex);

    glBindVertexArray(renderer->VAO);


    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}