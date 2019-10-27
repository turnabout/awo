#include <cglm/cglm.h>

#include "Game/_game.h"

void init_projection_matrix(Game* game, mat4 projection_matrix, int w, int h);
GLuint make_VAO();

static GLuint sprite_sheet_texture;
static GLuint VAO;

void update_game(Game* game, float delta_time)
{
}

void render_game(Game* game)
{
    glUseProgram(game->shader_program);

    glActiveTexture(GL_TEXTURE0); 
    glBindTexture(GL_TEXTURE_2D, game->sprite_sheet);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
}

void run_game(Game* game)
{
    int game_w, game_h;
    mat4 main_projection;
    glfwGetWindowSize(game->window, &game_w, &game_h);
    init_projection_matrix(game, main_projection, game_w, game_h);

    glUseProgram(game->shader_program);
    glUniformMatrix4fv(glGetUniformLocation(game->shader_program, "projection"), 1, GL_FALSE, main_projection[0]);

    VAO = make_VAO();

    // --------------------------------------------------------------------------------------------
    // 
    // Start of actual final loop code
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

GLuint make_VAO()
{
    GLuint VAO;
    GLfloat vertices[] = {
        // Pos      // Tex
        0.0f, 1.0f, 0.0f, 1.0f, // Top left
        1.0f, 0.0f, 1.0f, 0.0f, // Bottom right
        0.0f, 0.0f, 0.0f, 0.0f, // Bottom left

        0.0f, 1.0f, 0.0f, 1.0f, // Top left
        1.0f, 1.0f, 1.0f, 1.0f, // Top right
        1.0f, 0.0f, 1.0f, 0.0f, // Bottom right
    };

    // VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBO
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Vertex attribute
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    return VAO;
}

void init_projection_matrix(Game* game, mat4 projection_matrix, int w, int h)
{
    glm_ortho(0.0f, (float)w, 0.0f, (float)h, -1.0f, 1.0f, projection_matrix);
}