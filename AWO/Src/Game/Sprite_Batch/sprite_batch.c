#include <stdlib.h>
#include <cglm/cglm.h>// TODO: temp, remove

#include "Game/Sprite_Batch/sprite_batch.h"

static mat4 texture_projection; // TODO: temporary, remove

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

    // Set texture projection matrix TODO: temporary, remove
    int ss_w = 628, ss_h = 396;
    glm_ortho(0.0f, (float)ss_w, (float)ss_h, 0.0f, -1.0f, 1.0f, texture_projection);

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

// TODO: Need to take in dimensions (width/height) vec2
void add_to_sprite_batch(Sprite_Batch* sprite_batch, vec2 dst, vec4 tex_data)
{
    vec4 top_left     = {tex_data[0],               tex_data[1],               0.0f, 1.0f};
    vec4 top_right    = {tex_data[0] + tex_data[2], tex_data[1],               0.0f, 1.0f};
    vec4 bottom_left  = {tex_data[0],               tex_data[1] + tex_data[3], 0.0f, 1.0f};
    vec4 bottom_right = {tex_data[0] + tex_data[2], tex_data[1] + tex_data[3], 0.0f, 1.0f};

    // Transform texture data into Normalized Device Coordinates
    // TODO: tex_data will need to have been normalized beforehand, do this elsewhere
    glm_mat4_mulv(texture_projection, top_left, top_left);
    glm_mat4_mulv(texture_projection, top_right, top_right);
    glm_mat4_mulv(texture_projection, bottom_left, bottom_left);
    glm_mat4_mulv(texture_projection, bottom_right, bottom_right);

    top_left[0]     = (top_left[0] / 2) + 0.50f;
    top_left[1]     = (top_left[1] / 2) + 0.50f;
    top_right[0]    = (top_right[0] / 2) + 0.50f;
    top_right[1]    = (top_right[1] / 2) + 0.50f;
    bottom_left[0]  = (bottom_left[0] / 2) + 0.50f;
    bottom_left[1]  = (bottom_left[1] / 2) + 0.50f;
    bottom_right[0] = (bottom_right[0] / 2) + 0.50f;
    bottom_right[1] = (bottom_right[1] / 2) + 0.50f;

    // Set the quad's vertices data
    GLfloat quad_vertices[] = {
        // Pos                                      // Tex
        dst[0],               dst[1] + tex_data[3], top_left[0],     top_left[1],     // Top left
        dst[0] + tex_data[2], dst[1] + tex_data[3], top_right[0],    top_right[1],    // Top right
        dst[0],               dst[1],               bottom_left[0],  bottom_left[1],  // Bot. left
        dst[0] + tex_data[2], dst[1],               bottom_right[0], bottom_right[1], // Bot. right
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