#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef struct Sprite_Sheet_Data Sprite_Sheet_Data;

Sprite_Sheet_Data* create_sprite_sheet_data();

GLuint get_sprite_sheet_GL_texture(Sprite_Sheet_Data* data);

void get_sprite_sheet_dimensions(Sprite_Sheet_Data* data, int* width, int* height);

void free_sprite_sheet_data(Sprite_Sheet_Data* data);
