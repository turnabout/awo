#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Creates a shader_program program, using the given paths to the vertex and fragment shaders.
// Returns the shader_program program ID or 0 if unsuccessful.
GLuint create_shader_program(const char* vertex_shader_path, const char* fragment_shader_path);

// Creates a texture object from an image loaded at the given path.
// Returns the texture object ID or 0 if unsuccessful.
GLuint create_texture_object(const char* path);