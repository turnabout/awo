#include <stdlib.h>

#include "Game/Sprite_Batch/sprite_batch.h"
#include "Game/Data/Animation/animation.h"

/* How many elements are included in a single vertex:
 * - Destination x & y
 * - Texture x & y
 * - Palette index
 */
#define VERTEX_FLOAT_COUNT 5

// How many vertices make up a full quad (4)
#define QUAD_VERTICES_AMOUNT 4

struct Sprite_Batch {
    GLuint VAO;
    GLuint shader_program;
    GLuint sprite_sheet_texture;
    GLuint palettes_texture;
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

    // Reserve VBO memory (one 2D quad's data requires 4 vertices of 5 floats each)
    size_t quad_size = (sizeof(GLfloat) * VERTEX_FLOAT_COUNT) * QUAD_VERTICES_AMOUNT;
    glBufferData(GL_ARRAY_BUFFER, quad_size * max_elements, NULL, GL_DYNAMIC_DRAW);

    // EBO
    GLuint indices[] = {
        0, 1, 2, // First triangle
        2, 1, 3, // Second triangle
    };

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    size_t stride = VERTEX_FLOAT_COUNT * sizeof(GLfloat);

    // Vertex attribute for destination position
    glVertexAttribPointer(
        0, 
        2, 
        GL_FLOAT, 
        GL_FALSE, 
        stride, 
        (void*)(0 * sizeof(GLfloat))
    );
    glEnableVertexAttribArray(0);

    // Vertex attribute for texture position
    glVertexAttribPointer(
        1, 
        2, 
        GL_FLOAT, 
        GL_FALSE, 
        stride, 
        (void*)(2 * sizeof(GLfloat))
    );
    glEnableVertexAttribArray(1);

    // Vertex attribute for texture position
    glVertexAttribPointer(
        2, 
        1, 
        GL_FLOAT, 
        GL_FALSE, 
        stride, 
        (void*)(4 * sizeof(GLfloat))
    );
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

Sprite_Batch* create_sprite_batch(
    GLuint shader_program, 
    GLuint sprite_sheet_texture, 
    GLuint palette_texture, 
    int max_elements
)
{
    Sprite_Batch* sprite_batch = (Sprite_Batch*)malloc(sizeof(Sprite_Batch));

    init_sprite_batch_data(sprite_batch, max_elements);

    sprite_batch->shader_program = shader_program;
    sprite_batch->sprite_sheet_texture = sprite_sheet_texture;
    sprite_batch->palettes_texture = palette_texture;
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

    glActiveTexture(GL_TEXTURE1); 
    glBindTexture(GL_TEXTURE_2D, sprite_batch->palettes_texture);

    glBindVertexArray(sprite_batch->VAO);

    // Reset amount of elements queued
    sprite_batch->elements_queued = 0;
}

void add_to_sprite_batch(
    Sprite_Batch* sprite_batch, 
    vec2 dst, 
    Frame* frame_data, 
    GLfloat palette_index
)
{
    // Set the quad's vertices data
    GLfloat quad_vertices[QUAD_VERTICES_AMOUNT][VERTEX_FLOAT_COUNT] = {

        // Top left
        { 
            dst[0], dst[1] + frame_data->dimensions[1],       // <vec2> Destination
            frame_data->top_left[0], frame_data->top_left[1], // <vec2> Texture
            palette_index                                     // <float> Palette index
        },     

        // Top right
        {
            dst[0] + frame_data->dimensions[0], dst[1] + frame_data->dimensions[1],
            frame_data->top_right[0], frame_data->top_right[1],
            palette_index
        },

        // Bottom left
        {
            dst[0], dst[1], 
            frame_data->bottom_left[0],frame_data->bottom_left[1],
            palette_index
        },

        // Bottom right
        {
            dst[0] + frame_data->dimensions[0], dst[1], 
            frame_data->bottom_right[0], frame_data->bottom_right[1],
            palette_index
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

void add_to_sprite_batch__test_palette(Sprite_Batch* sprite_batch)
{
    #define LG_BOTTOM 600
    #define SM_BOTTOM 800

    #define LEFT   0
    #define RIGHT  255
    #define TOP    801
    #define BOTTOM LG_BOTTOM

    GLfloat quad_vertices[QUAD_VERTICES_AMOUNT][VERTEX_FLOAT_COUNT] = {
        {LEFT, TOP, 0.0, 0.0, 0.0}, // Top left
        {RIGHT, TOP, 1.0, 0.0, 0.0}, // Top right
        {LEFT, BOTTOM, 0.0, 1.0, 0.0}, // Bottom left
        {RIGHT, BOTTOM, 1.0, 1.0, 0.0}, // Bottom right
    };

    // Store vertices data in previously allocated buffer
    // TODO: change offset as we add more elements to sprite batch queue
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(quad_vertices), quad_vertices);
}