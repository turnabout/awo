#include <string.h>
#include <stdlib.h>

#include "Stage/_stage.h"
#include "Player/player_index_enum.h"
#include "Utilities/utilities.h"

Stage* generate_filled_stage(
    Tile_Type type, 
    Tile_Variation variation, 
    Uint8 width,
    Uint8 height
)
{
    Stage* stage = create_stage(
        "Default stage",
        width,
        height,
        (Army_Type[MAX_PLAYER_COUNT]){OS, BM, ARMY_TYPE_NONE, ARMY_TYPE_NONE}
    );

    // Fill entire grid with tiles of given type & variation
    fill_stage_tiles(stage, type, variation);

    // Add player HQ tiles so the stage is valid
    edit_stage_tile(stage, 0, 0, Property_HQ, Player_Index_0);
    edit_stage_tile(stage, 1, 0, Property_HQ, Player_Index_1);

    return stage;
}
