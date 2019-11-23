#include <string.h>
#include <stdlib.h>

#include "Game/Stage/_stage_descriptor.h"
#include "Game/Player/player_index_enum.h"
#include "Utilities/utilities.h"

Stage_Descriptor* generate_custom_stage()
{
    Stage_Descriptor* stage = (Stage_Descriptor*)malloc(sizeof(Stage_Descriptor));

    strcpy(stage->name, "Custom stage");

    // Add stage metadata
    stage->width = 10;
    stage->height = 10;
    stage->tile_count = stage->width * stage->height;

    stage->tile_descriptors = (Tile_Descriptor*)malloc(
        sizeof(Tile_Descriptor) * stage->tile_count
    );

    // Add some default stage players data
    for (int i = 0; i < MAX_PLAYER_COUNT; i++) {
        stage->player_armies[i] = ARMY_TYPE_NONE;
    }

    stage->player_count = 2;
    stage->player_armies[0] = OS;
    stage->player_armies[1] = GE;

    // Add default tiles
    for (int i = 0; i < stage->tile_count; i++) {
        stage->tile_descriptors[i].type = Plain;
        stage->tile_descriptors[i].variation = Default;
    }

    // Add initial player HQ tiles so the stage is valid
    stage->tile_descriptors[stage->tile_count - 1].type = Property_HQ;
    stage->tile_descriptors[stage->tile_count - 1].variation = Player_Index_0;

    stage->tile_descriptors[stage->tile_count - 2].type = Property_HQ;
    stage->tile_descriptors[stage->tile_count - 2].variation = Player_Index_1;

    stage->tile_descriptors[0].type = Property_City;
    stage->tile_descriptors[0].variation = Player_Index_0;

    stage->tile_descriptors[1].type = Property_Airport;
    stage->tile_descriptors[1].variation = Player_Index_0;

    stage->tile_descriptors[2].type = Property_Port;
    stage->tile_descriptors[2].variation = Player_Index_0;

    stage->tile_descriptors[21].type = Property_Base;
    stage->tile_descriptors[21].variation = Player_Index_Neutral;

    return stage;
}
