#include <cglm/cglm.h>

#include "Game/_game.h"
#include "Game/Sprite_Batch/sprite_batch.h"

void update_game(Game* game, float delta_time)
{
}

void render_game(Game* game)
{
    // Draw main sprites
    begin_sprite_batch(game->sprite_batches[SPRITES_SPRITE_BATCH]);

    // Test sprite 1
    add_to_sprite_batch(
        game->sprite_batches[SPRITES_SPRITE_BATCH], 
        (vec2) { 500, 500 }, 
        (vec4) {549, 64, 15, 16}
    );
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // Test sprite 2
    /*
    add_to_sprite_batch(
        game->sprite_batches[SPRITES_SPRITE_BATCH], 
        (vec2) { 515, 500 }, 
        (vec4) {549, 16, 15, 16}
    );
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    */

    end_sprite_batch(game->sprite_batches[SPRITES_SPRITE_BATCH]);
}

void run_game(Game* game)
{
    static float delta_time = 0.0f;      // Time between current frame and last frame.
    static float last_frame_time = 0.0f; // Time of last frame.

    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(game->window)) {

        // Update delta time
        float current_frame_time = (float)glfwGetTime();
        delta_time = current_frame_time - last_frame_time;
        last_frame_time = current_frame_time;

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        render_game(game);

        glfwSwapBuffers(game->window);
    }
}


/*
GLuint make_VAO(Game* game)
{
    // VAO
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBO
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Reserve VBO memory (one 2D quad requires 4 vertices of 4 floats each)
    size_t quad_size = (sizeof(GLfloat) * 4) * 4;
    glBufferData(GL_ARRAY_BUFFER, quad_size, NULL, GL_DYNAMIC_DRAW);

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

    return VAO;
}
*/
