#pragma once
#include <SDL.h>

#include "cJSON.h"

// An animation and its frames.
typedef struct Animation
{
    int count;
    SDL_Rect* frames;
} Animation;

// Creates and populates an animation struct using data from a cJSON animation array.
Animation* Anim_create_from_JSON(const cJSON* animation_json);

// Frees an animation's allocated memory.
void Anim_free(Animation* animation_data);

#ifdef _DEBUG
// Prints an Animation's contents.
void Anim_print(Animation* animation_data);
#endif
