#pragma once
#include <SDL.h>
#include "units.h"

/**
 * \brief Represents an animation and its frames.
 */
typedef struct Animation
{
    int count;
    SDL_Rect* frames;
} Animation;

/**
 * \brief Represents all visual data used by units.
 */
typedef struct Units_Data
{
    Animation* src[UNIT_TYPE_AMOUNT][UNIT_VAR_AMOUNT][UNIT_ANIM_AMOUNT];
} Units_Data;
