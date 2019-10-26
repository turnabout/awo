#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLuint create_shader_program(const char* vertex_shader_path, const char* fragment_shader_path);