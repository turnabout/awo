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
 * \brief Represents a unit's variation and its animations.
 */
typedef struct Src_Unit_Type
{
    int count;         // How many unit Variations are contained within this unit type
    Animation*** vars; // Variations/Animations/Frames contained within this unit type
} Src_Unit_Type;

/**
 * \brief Represents all visual data used by units.
 */
typedef struct Units_Data
{
    Src_Unit_Type* src[UNIT_TYPE_AMOUNT];
} Units_Data;
