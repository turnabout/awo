#include "Game/Renderer/Render_Grid/render_grid.h"

GLuint get_render_grid_VAO(GLuint width, GLuint height, GLuint vertical_offset)
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

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // VBO
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    GLfloat left = 0.0f;
    GLfloat right = (GLfloat)width;
    GLfloat top = (GLfloat)height + (GLfloat)vertical_offset;
    GLfloat bottom = 0.0f + (GLfloat)vertical_offset;

    GLfloat quad_vertices[4][4] = {
        // Bottom left
        {
            left, bottom,  // Position
            0.0f, 1.0f,    // Texture coordinates
        }, 

        // Top left
        { 
            left, top,     // Position
            0.0f, 0.0f,    // Texture coordinates
        }, 

        // Top right
        { 
            right, top,    // Position
            1.0f, 0.0f,    // Texture coordinates
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

    return VAO;
}
