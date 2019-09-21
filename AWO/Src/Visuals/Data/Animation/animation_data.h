#pragma once
#include <SDL.h>
#include "conf.h"
#include "cJSON.h"

typedef struct Animation
{
    int count;
    SDL_Rect* frames;
} Animation;

/**
 *  \brief Creates and populates an Animation struct using data from a cJSON animation array.
 *
 *  \param animation_json Pointer to the cJSON animation array.
 *
 *  \return Returns pointer to the allocated Animation struct.
 */
Animation* AD_create_from_JSON(const cJSON* animation_json);

/**
 *  \brief Destroys an Animation's allocated memory.
 *
 *  \param animation_data Pointer to the allocated Animation.
 */
void AD_free(Animation* animation_data);

#ifdef _DEBUG
/**
 *  \brief Prints an Animation's contents.
 *
 *  \param animation_data Pointer to the allocated Animation.
 */
void AD_print(Animation* animation_data);
#endif
