#pragma once
#include <SDL.h>

#include "Data/Palettes/palette_tree.h"
#include "Data/Units/units_enums.h"

/**
 * \brief Represents an animation and its frames.
 */
typedef struct
{
    int count;
    SDL_Rect* frames;
} Animation;

/**
 * \brief Represents the sprite sheet meta data for a data structure.
 */
typedef struct
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
typedef struct
{
    int vars_count;    // How many unit Variations are contained within this unit type
    Animation*** vars; // Variations/Animations/Frames contained within this unit type
} Src_Unit_Type;

/**
 * \brief Represents a palette for a unit variation.
 */
typedef struct
{
    int flip;
    Palette_Node* palette;
} Unit_Palette;

/**
 * \brief Represents all visual data used by units.
 */
typedef struct
{
    Src_Unit_Type* src[UNIT_TYPE_AMOUNT];
    Animation* dst[UNIT_TYPE_AMOUNT][UNIT_ANIM_FULL_AMOUNT];
    SS_Meta_Data* ss_meta_data;
} Units_Data;

/**
 *  \brief Gets a unit's variation's source animations data.
 *
 *  \param type The Unit Type.
 *
 *  \param var The Unit Variation.
 *
 *  \return Returns the array of Animation arrays for the given unit type & variation.
 *          If the given variation does not exist on the given unit type, returns the data for the
 *          default unit variation.
 */
Animation** access_unit_src_anims(unit_type type, unit_var var);

/**
 *  \brief Gets a unit's destination animations data.
 *
 *  \param type The Unit Type.
 *
 *  \return Returns the array of Animation arrays for the given unit type.
 */
Animation** access_unit_dst_anims(unit_type type);

/**
 *  \brief Access units' sprite sheet meta data.
 *
 *  \return Returns the Animation for the given Unit/Animation.
 */
SS_Meta_Data* access_units_ss_meta_data();

/**
 *  \brief Get the unit palette corresponding to the given unit variation.
 *
 *  \return Returns the unit palette.
 */
Unit_Palette* get_unit_palette(unit_var u_var);

void print_anim_contents(Animation* anim);
