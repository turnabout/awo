#pragma once

#include <cJSON.h>
#include <cglm/types.h>

#include "Game/Data/Tile/enums.h"
#include "Game/Data/Animation/animation.h"
#include "Game/Clock/Animation_Clock/enums.h"

// A tile variation's visual data
typedef struct Tile_Variation_Data
{
    // Index to animation sub clock used by this tile variation to update its animation.
    Animation_Sub_Clock_Index sub_clock; 

    // This tile variation's animation.
    Animation* animation;
} Tile_Variation_Data;

/*! @brief Creates tile variation data from the given JSON.
 *
 *  @param[in] tile_variation_string Short string representing the tile variation.
 *  @param[in] tile_type_JSON The JSON object of this tile variation's tile type.
 *  @param[in] ss_width The tiles_width of the game's sprite sheet.
 *  @param[in] ss_height The tiles_height of the game's sprite sheet.
 */
Tile_Variation_Data* create_tile_variation_data(
    char* tile_variation_string,
    cJSON* tile_type_JSON,
    int ss_width,
    int ss_height
);

/*! @brief Frees all data used up by the given tile variation data object.
 *
 *  @param[in] tile_variation_data The tile variation data object to free.
 */
void free_tile_variation_data(Tile_Variation_Data* tile_variation_data);
