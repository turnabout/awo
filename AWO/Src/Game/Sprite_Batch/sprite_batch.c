#include <stdlib.h>

#include "Game/Sprite_Batch/sprite_batch.h"
#include "Game/Data/Animation/animation.h"

struct Sprite_Batch {
    GLuint VAO;
    GLuint shader_program;
    GLuint sprite_sheet_texture;
    int elements_queued;
    int elements_max;
};

void init_sprite_batch_data(Sprite_Batch* sprite_batch, int max_elements)
{
    // VAO
    glGenVertexArrays(1, &sprite_batch->VAO);
    glBindVertexArray(sprite_batch->VAO);

    // VBO
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Reserve VBO memory (one 2D quad's data requires 4 vertices of 4 floats each)
    size_t element_size = (sizeof(GLfloat) * 4) * 4;
    glBufferData(GL_ARRAY_BUFFER, element_size * max_elements, NULL, GL_DYNAMIC_DRAW);

    // EBO
    GLuint indices[] = {
        0, 1, 2, // First triangle
        2, 1, 3, // Second triangle
    };

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Vertex attributes
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

Sprite_Batch* create_sprite_batch(GLuint shader_program, GLuint sprite_sheet_texture, int max_elements)
{
    Sprite_Batch* sprite_batch = (Sprite_Batch*)malloc(sizeof(Sprite_Batch));

    init_sprite_batch_data(sprite_batch, max_elements);

    sprite_batch->shader_program = shader_program;
    sprite_batch->sprite_sheet_texture = sprite_sheet_texture;
    sprite_batch->elements_max = max_elements;
    sprite_batch->elements_queued = 0;

    return sprite_batch;
}

void begin_sprite_batch(Sprite_Batch* sprite_batch)
{
    // Set active sprite sheet texture/shader program/VAO
    glUseProgram(sprite_batch->shader_program);

    glActiveTexture(GL_TEXTURE0); 
    glBindTexture(GL_TEXTURE_2D, sprite_batch->sprite_sheet_texture);

    glBindVertexArray(sprite_batch->VAO);

    // Reset amount of elements queued
    sprite_batch->elements_queued = 0;
}

void add_to_sprite_batch(Sprite_Batch* sprite_batch, vec2 dst, Frame* frame_data)
{
    // Set the quad's vertices data
    // TODO: un-hardcode [4][4]
    GLfloat quad_vertices[4][4] = {

        // Top left
        { 
            dst[0], dst[1] + frame_data->dimensions[1],      // Destination
            frame_data->top_left[0], frame_data->top_left[1] // Texture
        },     

        // Top right
        {
            dst[0] + frame_data->dimensions[0], dst[1] + frame_data->dimensions[1],
            frame_data->top_right[0], frame_data->top_right[1]
        },

        // Bottom left
        {
            dst[0], dst[1], 
            frame_data->bottom_left[0],frame_data->bottom_left[1]
        },

        // Bottom right
        {
            dst[0] + frame_data->dimensions[0], dst[1], 
            frame_data->bottom_right[0], frame_data->bottom_right[1]
        }

    };

    // Store vertices data in previously allocated buffer
    // TODO: change offset as we add more elements to sprite batch queue
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(quad_vertices), quad_vertices);

    // Update sprite batch state
    sprite_batch->elements_queued++;
}

void end_sprite_batch(Sprite_Batch* sprite_batch)
{
    glUseProgram(0);
    glBindVertexArray(0);
}

void free_sprite_batch(Sprite_Batch* sprite_batch)
{
    free(sprite_batch);
}