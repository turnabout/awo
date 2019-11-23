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
    Stage* stage = (Stage*)malloc(sizeof(Stage));

    strcpy(stage->name, "Default stage");

    // Add stage metadata
    stage->width = width;
    stage->height = height;
    stage->tile_count = width * height;

    stage->tiles = (Stage_Tile*)malloc(
        sizeof(Stage_Tile) * stage->tile_count
    );

    // Add some default stage players data
    for (int i = 0; i < MAX_PLAYER_COUNT; i++) {
        stage->player_armies[i] = ARMY_TYPE_NONE;
    }

    stage->player_count = 2;
    stage->player_armies[0] = OS;
    stage->player_armies[1] = BM;

    // Add initial player HQ tiles so the stage is valid
    stage->tiles[0].type = Property_HQ;
    stage->tiles[0].variation = Player_Index_0;

    stage->tiles[1].type = Property_HQ;
    stage->tiles[1].variation = Player_Index_1;

    // Add all other tiles
    for (int i = stage->player_count; i < stage->tile_count; i++) {
        stage->tiles[i].type = type;
        stage->tiles[i].variation = variation;
    }

    return stage;
}
