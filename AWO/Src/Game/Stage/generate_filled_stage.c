#include <string.h>
#include <stdlib.h>

#include "Game/Stage/_stage_descriptor.h"
#include "Game/Player/player_index_enum.h"
#include "Utilities/utilities.h"

Stage_Descriptor* generate_filled_stage(
    Tile_Type type, 
    Tile_Variation variation, 
    Uint8 width,
    Uint8 height
)
{
    Stage_Descriptor* stage = (Stage_Descriptor*)malloc(sizeof(Stage_Descriptor));

    strcpy(stage->name, "Default stage");

    // Add stage metadata
    stage->width = width;
    stage->height = height;
    stage->tile_count = width * height;

    stage->tile_descriptors = (Tile_Descriptor*)malloc(
        sizeof(Tile_Descriptor) * stage->tile_count
    );

    // Add some default stage players data
    stage->player_count = 2;
    stage->player_armies[0] = OS;
    stage->player_armies[1] = BM;

    // Add initial player HQ tiles so the stage is valid
    stage->tile_descriptors[0].type = Property_HQ;
    stage->tile_descriptors[0].variation = Player_Index_0;

    stage->tile_descriptors[1].type = Property_HQ;
    stage->tile_descriptors[1].variation = Player_Index_1;

    // Add all other tiles
    for (int i = stage->player_count; i < stage->tile_count; i++) {
        stage->tile_descriptors[i].type = type;
        stage->tile_descriptors[i].variation = variation;
    }

    return stage;
}
