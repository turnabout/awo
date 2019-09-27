#pragma once

#include "cJSON.h"
#include "units_enums.h"

#include "Visuals/Data/Sprite_Sheet_Metadata/ss_metadata.h"
#include "Visuals/Data/Palette/palette_tree.h"
#include "Visuals/Data/Animation/animation.h"

// Holds all of the game's visuals data for units.
typedef struct Units_Data Units_Data;

// Creates units data object from JSON.
Units_Data* UD_create_from_JSON(const cJSON* ud_JSON);

// Gets the source animations data for a unit type & variation.
Animation** UD_get_src_anims(Units_Data* ud, Unit_Type u_type, Unit_Var u_var);

// Gets the destination animations data for a unit type & variation.
Animation** UD_get_dst_anims(Units_Data* ud, Unit_Type u_type);

// Gets the units sprite sheet metadata.
SS_Metadata* UD_get_ss_metadata(Units_Data* ud);

// Gets the palette for the given unit color variation.
// \param u_var The unit color variation for which to get the palette.
// \param flip Pointer where the resulting "flip" value of this palette gets stored.
Palette_Tree* UD_get_palette(Units_Data* ud, Unit_Var u_var, int* flip);

#ifdef _DEBUG
// Argument given to UD_print telling it which part of units data to print.
typedef enum {
    UD_SRC,
    UD_DST,
} UD_print_arg;

// Prints the contents from units data.
void UD_print(Units_Data* ud, UD_print_arg which);
#endif
