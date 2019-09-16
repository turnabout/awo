#pragma once
#include <SDL.h>

#include "Data/Palettes/palette_tree.h"
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
 * \brief Represents the sprite sheet meta data for a data structure.
 */
typedef struct SS_Meta_Data
{
    int src_x;
    int src_y;
    int src_width;
    int src_height;
    int dst_width;
    int dst_height;
} SS_Meta_Data;

/**
 * \brief Represents a unit's variation and its animations.
 */
typedef struct Src_Unit_Type
{
    int vars_count;    // How many unit Variations are contained within this unit type
    Animation*** vars; // Variations/Animations/Frames contained within this unit type
} Src_Unit_Type;

/**
 * \brief Represents a palette for a unit variation.
 */
typedef struct Unit_Palette
{
    int flip;
    Palette_Node* palette;
} Unit_Palette;

/**
 * \brief Represents all visual data used by units.
 */
typedef struct Units_Data
{
    Src_Unit_Type* src[UNIT_TYPE_AMOUNT];
    Animation* dst[UNIT_TYPE_AMOUNT][UNIT_ANIM_FULL_AMOUNT];
    SS_Meta_Data* ss_meta_data;
    Palette_Node* base_palette;
    Unit_Palette* unit_palettes;
} Units_Data;

/**
 *  \brief Gets a Unit's Variation data.
 *
 *  \param type The Unit Type.
 *
 *  \param var The Unit Variation.
 *
 *  \return Returns the array of Animation arrays for the given unit type & variation.
 *          If the given variation does not exist on the given unit type, returns the data for the
 *          default unit variation.
 */
Animation** access_unit_src_var(unit_type type, unit_var var);

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
 */
Animation* access_unit_src_animation(unit_type type, unit_var var, unit_anim anim);

/**
 *  \brief Gets a Unit's Animation destination data.
 *
 *  \param type The Unit Type.
 *
 *  \param anim The Unit Animation.
 *
 *  \return Returns the Animation for the given Unit/Animation.
 */
Animation* access_unit_dst_animation(unit_type type, unit_anim anim);

/**
 *  \brief Access units' sprite sheet meta data.
 *
 *  \return Returns the Animation for the given Unit/Animation.
 */
SS_Meta_Data* access_units_ss_meta_data();

void print_anim_contents(Animation* anim);
