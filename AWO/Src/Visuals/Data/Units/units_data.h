#pragma once

#include "cJSON.h"
#include "units_enums.h"
#include "../Sprite_Sheet_Metadata/ss_metadata.h"
#include "../Palette/palette_tree.h"
#include "../Animation/animation_data.h"

/**
 *  \brief Holds all of the game's visuals data for units.
 */
typedef struct Units_Data Units_Data;

/**
 *  \brief Create units data object from JSON.
 *
 *  \param units_visuals_JSON The cJSON object containing units' JSON.
 *
 *  \return Returns the initialized units' data.
 */
Units_Data* UD_create_from_JSON(const cJSON* ud_JSON);

/**
 *  \brief Gets the source animations data for a unit type & variation.
 *
 *  \param ud The units data object.
 *
 *  \param u_type The unit type to get the data from.
 *
 *  \param u_var The unit variation to get the data from.
 *
 *  \return Returns a pointer to the animations.
 */
Animation** UD_get_src_anims(Units_Data* ud, unit_type u_type, unit_var u_var);

/**
 *  \brief Gets the destination animations data for a unit type & variation.
 *
 *  \param ud The units data object.
 *
 *  \param u_type The unit type to get the data from.
 *
 *  \return Returns a pointer to the animations.
 */
Animation** UD_get_dst_anims(Units_Data* ud, unit_type u_type);

/**
 *  \brief Get the units sprite sheet metadata.
 *
 *  \param ud Units data object.
 *
 *  \return Returns the sprite sheet metadata.
 */
SS_Metadata* UD_get_ss_metadata(Units_Data* ud);

/**
 *  \brief Get the palette for the given unit color variation.
 *
 *  \param ud Units data object.
 *
 *  \param u_var The unit color variation for which to get the palette.
 *
 *  \param flip Stores the "flip" value of this palette.
 *
 *  \return Returns the sprite sheet metadata.
 */
Palette_Tree* UD_get_palette(Units_Data* ud, unit_var u_var, int* flip);

#ifdef _DEBUG

typedef enum {
    UD_SRC,
    UD_DST,
} UD_print_arg;

/**
 *  \brief Print contents from units data.
 *
 *  \param ud The Units_Data object to print.
 *
 *  \param which Which part of the units' data to print.
 */
void UD_print(Units_Data* ud, UD_print_arg which);
#endif
