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
    GLuint palettes_tex;
    GLuint tiles_tex;

    // Width
    GLuint width;
    GLuint height;
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

    GLfloat top = (GLfloat)renderer->height;
    GLfloat right = (GLfloat)renderer->width;

    GLfloat quad_vertices[4][4] = {
        // Bottom left
        {
            0, 0,       // Position
            0.0f, 1.0f, // Texture coordinates
        }, 

        // Top left
        { 
            0, top,     // Position
            0.0f, 0.0f, // Texture coordinates
        }, 

        // Top right
        { 
            right, top, // Position
            1.0f, 0.0f, // Texture coordinates
        }, 

        // Bottom right
        { 
            right, 0,   // Position
            1.0f, 1.0f, // Texture coordinates
        }, 
    };

    glBufferData(GL_ARRAY_BUFFER, quad_size, quad_vertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void*)(0 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
}

typedef GLfloat Tiles_Texture_Row[DEFAULT_GAME_BOARD_WIDTH][4];

void init_tiles_texture(Renderer* renderer)
{
    Tiles_Texture_Row* tiles_texture_data = malloc(sizeof(Tiles_Texture_Row) * DEFAULT_GAME_BOARD_HEIGHT);

    for (int i = 0; i < DEFAULT_GAME_BOARD_HEIGHT; i++) {
        for (int j = 0; j < DEFAULT_GAME_BOARD_WIDTH; j++) {
            tiles_texture_data[i][j][0] = 1.0f;
            tiles_texture_data[i][j][1] = 1.0f;
            tiles_texture_data[i][j][2] = 0.0f;
            tiles_texture_data[i][j][3] = 1.0f;
        }
    }

    glGenTextures(1, &renderer->tiles_tex);
    glBindTexture(GL_TEXTURE_2D, renderer->tiles_tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, DEFAULT_GAME_BOARD_WIDTH, DEFAULT_GAME_BOARD_HEIGHT, 0, GL_RGBA, GL_FLOAT, tiles_texture_data);

    free(tiles_texture_data);
}

Renderer* create_renderer(
    GLuint sprite_sheet_tex, 
    GLuint palette_tex, 
    GLuint shader,
    GLuint width,
    GLuint height
)
{
    Renderer* renderer = (Renderer*)malloc(sizeof(Renderer));

    renderer->shader = shader;

    renderer->sprite_sheet_tex = sprite_sheet_tex;
    renderer->palettes_tex = palette_tex;
    renderer->width = width;
    renderer->height = height;

    glUseProgram(renderer->shader);

    init_renderer_buffer(renderer);
    init_tiles_texture(renderer);

    glUniform1i(glGetUniformLocation(renderer->shader, "sprite_sheet_texture"), 0);
    glUniform1i(glGetUniformLocation(renderer->shader, "tiles_texture"), 1);
    glUniform1i(glGetUniformLocation(renderer->shader, "palettes_texture"), 2);

    return renderer;
}

void render(Renderer* renderer, int x_offset, int y_offset)
{
    glUseProgram(renderer->shader);
    glBindVertexArray(renderer->VAO);

    glActiveTexture(GL_TEXTURE0); 
    glBindTexture(GL_TEXTURE_2D, renderer->sprite_sheet_tex);

    glActiveTexture(GL_TEXTURE1); 
    glBindTexture(GL_TEXTURE_2D, renderer->tiles_tex);

    glActiveTexture(GL_TEXTURE2); 
    glBindTexture(GL_TEXTURE_2D, renderer->palettes_tex);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void update_tiles_pixel(
    Renderer* renderer, 
    GLuint x,
    GLuint y,
    GLfloat R, 
    GLfloat G,
    GLfloat B
)
{
    glBindTexture(GL_TEXTURE_2D, renderer->tiles_tex);
    GLfloat new_color_array[4] = { R / 255.0f, G / 255.0f, B, 1.0f };

    glTexSubImage2D(
        GL_TEXTURE_2D,
        0,
        x,
        y,
        1,
        1,
        GL_RGBA,
        GL_FLOAT,
        &new_color_array
    );
}

void fill_tiles_palette_pixels(
    Renderer* renderer,
    GLfloat R,
    GLfloat G,
    GLfloat B
)
{
    glBindTexture(GL_TEXTURE_2D, renderer->tiles_tex);
    GLfloat new_color_array[4] = { R / 255.0f, G / 255.0f, B, 1.0f };

    for (int y = 0; y < (int)renderer->height; y++) {
        for (int x = 0; x < (int)renderer->width; x++) {
            glTexSubImage2D(
                GL_TEXTURE_2D,
                0,
                x,
                y,
                1,
                1,
                GL_RGBA,
                GL_FLOAT,
                &new_color_array
            );
        }
    }
}