#include "Game/Renderer/Tiles_Layer/tiles_layer.h"

GLuint get_tiles_layers_VAO(int tile_layers_width, int tile_layers_height)
{
    size_t stride = 4 * sizeof(GLfloat);
    size_t quad_size = 4 * stride;

    // VAO
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

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

    GLfloat right = (GLfloat)tile_layers_width;
    GLfloat top = (GLfloat)tile_layers_height;

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

    return VAO;
}
