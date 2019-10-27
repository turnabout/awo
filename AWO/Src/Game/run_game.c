#include <cglm/cglm.h>

#include "Game/_game.h"

GLuint make_VAO(Game* game);

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

    glm_ortho(0.0f, (float)game_w, 0.0f, (float)game_h, -1.0f, 1.0f, main_projection);

    glUseProgram(game->shader_program);
    glUniformMatrix4fv(glGetUniformLocation(game->shader_program, "projection"), 1, GL_FALSE, main_projection[0]);

    VAO = make_VAO(game);

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

GLuint make_VAO(Game* game)
{
    // Create projection matrix used to translate texture pixel coordinates to NDC
    mat4 texture_projection;
    int ss_w = 628;
    int ss_h = 396;

    glm_ortho(0.0f, (float)ss_w, (float)ss_h, 0.0f, -1.0f, 1.0f, texture_projection);

    glm_mat4_print(texture_projection, stdout);

    float dst_x  = 500.0f;
    float dst_y  = 500.0f;

    float tex_x = 549.0f;
    float tex_y = 64.0f;
    float tex_w = 15.0f;
    float tex_h = 16.0f;

    vec4 top_left     = {tex_x,     tex_y,     0.0f, 1.0f};
    vec4 top_right    = {tex_x + tex_w, tex_y,     0.0f, 1.0f};
    vec4 bottom_left  = {tex_x,     tex_y + tex_h, 0.0f, 1.0f};
    vec4 bottom_right = {tex_x + tex_w, tex_y + tex_h, 0.0f, 1.0f};

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

    glm_vec4_print(top_left, stdout);
    glm_vec4_print(top_right, stdout);
    glm_vec4_print(bottom_left, stdout);
    glm_vec4_print(bottom_right, stdout);

    GLuint VAO;
    GLfloat vertices[] = {
        // Pos      // Tex
        dst_x, dst_y + tex_h, top_left[0],     top_left[1],           // Top left
        dst_x + tex_w, dst_y, bottom_right[0], bottom_right[1],       // Bottom right
        dst_x, dst_y, bottom_left[0],  bottom_left[1],                // Bottom left

        dst_x, dst_y + tex_h, top_left[0],     top_left[1],           // Top left
        dst_x + tex_w, dst_y + tex_h, top_right[0],    top_right[1],  // Top right
        dst_x + tex_w, dst_y, bottom_right[0], bottom_right[1],       // Bottom right
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
