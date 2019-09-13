#pragma once
#include <SDL.h>
#include "Data/Units/units_enums.h"

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

/**
 *  \brief Gets a Unit's Animation source data.
 *
 *  \param type The Unit Type.
 *
 *  \param var The Unit Variation.
 *
 *  \param anim The Unit Animation.
 *
 *  \return Returns the Animation for the given Unit/Variation/Animation.
 *
 *  \sa access_unit_src_animation()
 */
Animation* access_unit_src_animation(enum unit_type type, enum unit_var var, enum unit_anim anim);

void print_anim_contents(Animation* anim);
