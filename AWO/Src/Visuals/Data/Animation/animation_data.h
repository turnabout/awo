#pragma once
#include <SDL.h>
#include "conf.h"
#include "cJSON.h"

// An animation and its frames.
typedef struct Animation
{
    int count;
    SDL_Rect* frames;
} Animation;

// Creates and populates an animation struct using data from a cJSON animation array.
Animation* AD_create_from_JSON(const cJSON* animation_json);

// Frees an animation's allocated memory.
void AD_free(Animation* animation_data);

#ifdef _DEBUG
// Prints an Animation's contents.
void AD_print(Animation* animation_data);
#endif
