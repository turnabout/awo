#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/types.h>

typedef struct Sprite_Batch Sprite_Batch;

typedef enum Sprite_Batch_Type {
    SPRITES_SPRITE_BATCH,
    FONTS_SPRITE_BATCH,
} Sprite_Batch_Type;

#define SPRITE_BATCH_TYPE_LAST  FONTS_SPRITE_BATCH
#define SPRITE_BATCH_TYPE_COUNT SPRITE_BATCH_TYPE_LAST + 1

Sprite_Batch* create_sprite_batch(GLuint shade_program, GLuint sprite_sheet_texture, int max_elements);

void begin_sprite_batch(Sprite_Batch* sprite_batch);
void add_to_sprite_batch(Sprite_Batch* sprite_batch, vec2 dst, vec4 tex_data);
void end_sprite_batch(Sprite_Batch* sprite_batch);

void free_sprite_batch(Sprite_Batch* sprite_batch);