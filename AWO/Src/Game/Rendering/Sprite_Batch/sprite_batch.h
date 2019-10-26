#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef struct Sprite_Batch Sprite_Batch;

Sprite_Batch* create_sprite_batch(GLuint VAO);

void begin_sprite_batch(Sprite_Batch* sprite_batch);
void add_to_sprite_batch(Sprite_Batch* sprite_batch);
void end_sprite_batch(Sprite_Batch* sprite_batch);