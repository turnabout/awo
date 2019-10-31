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

Tile_Variation_Data* create_tile_variation_data(
    char* tile_variation_string,
    cJSON* tile_type_JSON, 
    mat4 projection
);
