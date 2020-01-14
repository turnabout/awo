#pragma once

#include <cJSON.h>
#include <cglm/types.h>

#include "Game_Data/Animation/animation.h"
#include "Game_Data/Clock_Data/clock_data.h"
#include "Game_Data/Tile_Data/Tile_Type_Data/Tile_Variation_Data/Header/tile_variations.h"

// A tile variation's visual data
typedef struct Tile_Variation_Data
{

    // Index to the clock used by this tile variation to update its animation.
    Clock_Index clock;

    // This tile variation's animation.
    Animation* animation;

} Tile_Variation_Data;

/*! @brief Creates tile variation data from the given JSON.
 *
 *  @param[in] tile_var_JSON The JSON object of this tile variation.
 *  @param[in] ss_width The tiles_width of the game's sprite sheet.
 *  @param[in] ss_height The tiles_height of the game's sprite sheet.
 */
Tile_Variation_Data* create_tile_variation_data(
    cJSON* tile_var_JSON,
    int ss_width,
    int ss_height
);

/*! @brief Frees all data used up by the given tile variation data object.
 *
 *  @param[in] tile_variation_data The tile variation data object to free.
 */
void free_tile_variation_data(Tile_Variation_Data* tile_variation_data);
