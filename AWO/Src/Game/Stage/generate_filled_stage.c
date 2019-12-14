#include <string.h>
#include <stdlib.h>

#include "Game/Stage/_stage.h"
#include "Game/Player/player_index_enum.h"
#include "Utilities/utilities.h"

Stage* generate_filled_stage(
    Tile_Type type, 
    Tile_Variation variation, 
    Uint8 width,
    Uint8 height
)
{
    Stage* stage = malloc(sizeof(Stage));

    // Add stage metadata
    strcpy(stage->name, "Default stage");
    stage->width = width;
    stage->height = height;

    allocate_stage_grid(stage);

    // Add some default stage players data
    for (int i = 0; i < MAX_PLAYER_COUNT; i++) {
        stage->player_armies[i] = ARMY_TYPE_NONE;
    }

    stage->player_count = 2;
    stage->player_armies[0] = OS;
    stage->player_armies[1] = BM;

    // Fill entire grid with tiles of given type & variation
    fill_stage_tiles(stage, type, variation);

    // Add player HQ tiles so the stage is valid
    edit_stage_tile(stage, 0, 0, Property_HQ, Player_Index_0);
    edit_stage_tile(stage, 1, 0, Property_HQ, Player_Index_1);

    return stage;
}
