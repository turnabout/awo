#include <cglm/cglm.h>

#include "Game/_game.h"

GLuint make_VAO(Game* game);

static GLuint sprite_sheet_texture;
static GLuint VAO;
static mat4 texture_projection;

void add_to_sprite_batch_test(vec2 dst, vec4 tex_data)
{
    vec4 top_left     = {tex_data[0],               tex_data[1],               0.0f, 1.0f};
    vec4 top_right    = {tex_data[0] + tex_data[2], tex_data[1],               0.0f, 1.0f};
    vec4 bottom_left  = {tex_data[0],               tex_data[1] + tex_data[3], 0.0f, 1.0f};
    vec4 bottom_right = {tex_data[0] + tex_data[2], tex_data[1] + tex_data[3], 0.0f, 1.0f};

    // Transform texture data into Normalized Device Coordinates
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
        // Pos      // Tex
        dst[0],               dst[1] + tex_data[3], top_left[0],     top_left[1],     // Top left
        dst[0] + tex_data[2], dst[1],               bottom_right[0], bottom_right[1], // Bottom right
        dst[0],               dst[1],               bottom_left[0],  bottom_left[1],  // Bottom left

        dst[0],               dst[1] + tex_data[3], top_left[0],     top_left[1],     // Top left
        dst[0] + tex_data[2], dst[1] + tex_data[3], top_right[0],    top_right[1],    // Top right
        dst[0] + tex_data[2], dst[1],               bottom_right[0], bottom_right[1], // Bottom right
    };

    // Store vertices data in previously allocated buffer
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(quad_vertices), quad_vertices);
}

void update_game(Game* game, float delta_time)
{
}

void render_game(Game* game)
{
    glUseProgram(game->shader_program);

    glActiveTexture(GL_TEXTURE0); 
    glBindTexture(GL_TEXTURE_2D, game->sprite_sheet);


    glBindVertexArray(VAO);

    // Draw test sprite 1
    add_to_sprite_batch_test((vec2) { 500, 500 }, (vec4) {549, 64, 15, 16});
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Draw test sprite 2
    add_to_sprite_batch_test((vec2) { 515, 500 }, (vec4) {549, 16, 15, 16});
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
}

void run_game(Game* game)
{
    int game_w, game_h;
    mat4 main_projection;
    glfwGetWindowSize(game->window, &game_w, &game_h);

    // Set main projection matrix
    glm_ortho(0.0f, (float)game_w, 0.0f, (float)game_h, -1.0f, 1.0f, main_projection);

    glUseProgram(game->shader_program);
    glUniformMatrix4fv(glGetUniformLocation(game->shader_program, "projection"), 1, GL_FALSE, main_projection[0]);

    // Set texture projection matrix
    int ss_w = 628, ss_h = 396;
    glm_ortho(0.0f, (float)ss_w, (float)ss_h, 0.0f, -1.0f, 1.0f, texture_projection);


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
    // VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBO
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Reserve VBO memory (one 2D quad requires 6 vertices of 4 floats each)
    size_t quad_size = (sizeof(GLfloat) * 4) * 6;
    glBufferData(GL_ARRAY_BUFFER, quad_size, NULL, GL_DYNAMIC_DRAW);

    // Vertex attributes
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    return VAO;
}
