#include <stdlib.h>

#include "Game/Rendering/Sprite_Batch/sprite_batch.h"

struct Sprite_Batch {
    GLuint VAO;
};

Sprite_Batch* create_sprite_batch(GLuint VAO)
{
    Sprite_Batch* sprite_batch = (Sprite_Batch*)malloc(sizeof(Sprite_Batch));

    sprite_batch->VAO = VAO;

    return sprite_batch;
}

void begin_sprite_batch(Sprite_Batch* sprite_batch)
{
}

void add_to_sprite_batch(Sprite_Batch* sprite_batch)
{
}

void end_sprite_batch(Sprite_Batch* sprite_batch)
{
}