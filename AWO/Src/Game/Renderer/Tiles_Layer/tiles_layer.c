#include <stdlib.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "conf.h"
#include "GL_Helpers/gl_helpers.h"
#include "Game/Renderer/Tiles_Layer/tiles_layer.h"

struct Tiles_Layer {

    // Tiles layer's shader program.
    GLuint shader_program;

    // Tiles layer's VAO.
    GLuint VAO;

    // The raw sprite sheet texture.
    GLuint sprite_sheet_texture;

    // The palettes texture.
    GLuint palettes_texture;

    // The tiles layer texture.
    GLuint tiles_texture;

    // Width/height of the tiles layer, in tiles.
    int width, height;

    vec4* data4;
};

void init_renderer_buffer(Tiles_Layer* renderer)
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

void init_tiles_texture(Tiles_Layer* tiles_layer)
{
    glGenTextures(1, &tiles_layer->tiles_texture);
    glBindTexture(GL_TEXTURE_2D, tiles_layer->tiles_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(
        GL_TEXTURE_2D, 
        0, 
        GL_RGBA, 
        tiles_layer->width, 
        tiles_layer->height, 
        0, 
        GL_RGBA, 
        GL_FLOAT, 
        NULL
    );

    tiles_layer->data4 = malloc(sizeof(vec4) * tiles_layer->width * tiles_layer->height);
}

Tiles_Layer* create_tiles_layer(
    GLuint sprite_sheet_tex, 
    GLuint palette_tex, 
    GLuint shader,
    GLuint width,
    GLuint height
)
{
    Tiles_Layer* renderer = (Tiles_Layer*)malloc(sizeof(Tiles_Layer));

    renderer->shader_program = shader;

    renderer->sprite_sheet_texture = sprite_sheet_tex;
    renderer->palettes_texture = palette_tex;
    renderer->width = width;
    renderer->height = height;

    glUseProgram(renderer->shader_program);

    init_renderer_buffer(renderer);
    init_tiles_texture(renderer);

    glUniform1i(glGetUniformLocation(renderer->shader_program, "sprite_sheet_texture"), 0);
    glUniform1i(glGetUniformLocation(renderer->shader_program, "tiles_texture"), 1);
    glUniform1i(glGetUniformLocation(renderer->shader_program, "palettes_texture"), 2);

    return renderer;
}

void render_tiles_layer(Tiles_Layer* renderer)
{
    glUseProgram(renderer->shader_program);
    glBindVertexArray(renderer->VAO);

    glActiveTexture(GL_TEXTURE0); 
    glBindTexture(GL_TEXTURE_2D, renderer->sprite_sheet_texture);

    glActiveTexture(GL_TEXTURE1); 
    glBindTexture(GL_TEXTURE_2D, renderer->tiles_texture);

    // Update tiles texture with current contents of tiles_layer's texture data
    glTexSubImage2D(
        GL_TEXTURE_2D,
        0,
        0,
        0,
        renderer->width,
        renderer->height,
        GL_RGBA,
        GL_FLOAT,
        renderer->data4
    );

    glActiveTexture(GL_TEXTURE2); 
    glBindTexture(GL_TEXTURE_2D, renderer->palettes_texture);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void update_tiles_layer_mem(Tiles_Layer* tiles_layer, GLuint x, GLuint y, vec4 values)
{
    glBindTexture(GL_TEXTURE_2D, tiles_layer->tiles_texture);

    GLfloat stored_values[4] = {
        values[0] / 510.0f, 
        values[1] / 510.0f, 
        values[2], 
        values[3] 
    };

    memcpy(
        (tiles_layer->data4 + x + (y * tiles_layer->width)), 
        &stored_values, 
        sizeof(stored_values)
    );
}

void fill_tiles_layer_mem(Tiles_Layer* tiles_layer, vec4 values)
{
    glBindTexture(GL_TEXTURE_2D, tiles_layer->tiles_texture);

    GLfloat stored_values[4] = {
        values[0] / 510.0f, 
        values[1] / 510.0f, 
        values[2], 
        values[3] 
    };

    for (int y = 0; y < (int)tiles_layer->height; y++) {
        for (int x = 0; x < (int)tiles_layer->width; x++) {
            memcpy(
                (tiles_layer->data4 + x + (y * tiles_layer->width)), 
                &stored_values, 
                sizeof(stored_values)
            );
        }
    }
}

void update_tiles_layer_view_matrix(Tiles_Layer* tiles_layer, mat4 view)
{
    glUniformMatrix4fv(
        glGetUniformLocation(tiles_layer->shader_program, "view"), 1, GL_FALSE, view[0]
    );
}