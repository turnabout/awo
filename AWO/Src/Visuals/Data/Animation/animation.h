#pragma once
#include <SDL.h>

#include "cJSON.h"

// An animation and its frames.
typedef struct Animation Animation;

// Creates and populates an animation struct using data from a cJSON animation array.
Animation* anim_create_from_JSON(const cJSON* animation_json);

// Frees an animation's allocated memory.
void anim_free(Animation* animation_data);

// Gets pointer to the first frame in an animation.
// \param count Filled in with the amount of frames in the animation.
SDL_Rect* anim_get_frames(Animation* anim, int* count);

#ifdef _DEBUG
// Prints an Animation's contents.
void anim_print(Animation* animation_data);
#endif
