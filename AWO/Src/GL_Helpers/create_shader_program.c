#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Utilities/utilities.h"

GLuint check_shader_compile_errors(GLuint shader)
{
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char info_log[512];
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        printf("%s\n", info_log);
        return 0;
    }

    return 1;
}

GLuint check_shader_program_link_errors(GLuint shader_program)
{
    GLint success;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);

    if (!success) {
        char info_log[512];
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        printf("%s\n", info_log);
        return 0;
    }

    return 1;
}

GLuint create_shader(GLuint shader_type, const char* shader_source)
{
    // Create a vertex sprite_shader object
    GLuint shader = glCreateShader(shader_type);

    // Set the sprite_shader source code, compile it and then check for compilation errors
    glShaderSource(shader, 1, (const GLchar**)&shader_source, NULL);
    glCompileShader(shader);

    if (!check_shader_compile_errors(shader)) {
        return 0;
    }

    return shader;
}

GLuint create_shader_at_path(unsigned int shader_type, const char* file_path)
{
    // Get sprite_shader source
    char* shader_source_buffer;
    if ((shader_source_buffer = read_file(file_path)) == NULL) {
        return 0;
    }

    // Create and compile sprite_shader
    GLuint shader = create_shader(shader_type, shader_source_buffer);
    free(shader_source_buffer);

    return shader;
}

GLuint create_shader_program(const char* vertex_shader_path, const char* fragment_shader_path)
{
    GLuint shader_program;

    // Create & compile vertex & fragment sprite_shader objects
    GLuint vertex_shader = create_shader_at_path(GL_VERTEX_SHADER, vertex_shader_path);
    GLuint fragment_shader = create_shader_at_path(GL_FRAGMENT_SHADER, fragment_shader_path);

    if (!vertex_shader || !fragment_shader) {
        return 0;
    }

    // Create sprite_shader program by linking compiled shaders
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    // Delete now-unneeded sprite_shader objects
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // Check for linking errors
    if (!check_shader_program_link_errors(shader_program)) {
        return 0;
    }

    return shader_program;
}
