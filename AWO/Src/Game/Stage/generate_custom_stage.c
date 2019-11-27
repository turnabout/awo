#include <string.h>
#include <stdlib.h>

#include "Game/Stage/_stage.h"
#include "Game/Player/player_index_enum.h"
#include "Utilities/utilities.h"

void set_custom_stage_value(Stage* stage, int index, int type, int variation)
{
    stage->tiles[index].type = type;
    stage->tiles[index].variation = variation;
}

Stage* generate_custom_stage()
{
    Stage* stage = (Stage*)malloc(sizeof(Stage));

    strcpy(stage->name, "Custom stage");

    // Add stage metadata
    stage->width = 10;
    stage->height = 10;
    stage->tile_count = stage->width * stage->height;

    stage->tiles = (Stage_Tile*)malloc(
        sizeof(Stage_Tile) * stage->tile_count
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
        stage->tiles[i].type = Plain;
        stage->tiles[i].variation = Default;
    }

    // Add initial player HQ tiles so the stage is valid
    set_custom_stage_value(stage, stage->tile_count - 2, Property_HQ, Player_Index_1);

    // Some properties
    set_custom_stage_value(stage, 0, Property_City, Player_Index_0);
    set_custom_stage_value(stage, 1, Property_Airport, Player_Index_0);
    set_custom_stage_value(stage, 2, Property_Port, Player_Index_0);
    set_custom_stage_value(stage, 3, Property_HQ, Player_Index_0);

    set_custom_stage_value(stage, 21, Property_Base, Player_Index_0);

    // Sea
    set_custom_stage_value(stage, 23, Sea, TopLeft);
    set_custom_stage_value(stage, 24, Sea, Top);
    set_custom_stage_value(stage, 25, Sea, TopRight);

    set_custom_stage_value(stage, 33, Sea, DirLeft);
    set_custom_stage_value(stage, 34, Sea, Middle);
    set_custom_stage_value(stage, 35, Sea, DirRight);

    set_custom_stage_value(stage, 43, Sea, BottomLeft);
    set_custom_stage_value(stage, 44, Sea, Bottom);
    set_custom_stage_value(stage, 45, Sea, BottomRight);

    // Some roads & properties
    set_custom_stage_value(stage, 27, Road, TopLeft);
    set_custom_stage_value(stage, 28, Road, Horizontal);
    set_custom_stage_value(stage, 29, Road, Horizontal);

    set_custom_stage_value(stage, 38, Forest, TopLeft);
    set_custom_stage_value(stage, 39, Forest, TopRight);
    set_custom_stage_value(stage, 48, Forest, BottomLeft);
    set_custom_stage_value(stage, 49, Forest, BottomRight);

    set_custom_stage_value(stage, 37, Road, Vertical);
    set_custom_stage_value(stage, 47, Road, Vertical);

    set_custom_stage_value(stage, 53, Silo, Default);
    set_custom_stage_value(stage, 54, Property_City, Player_Index_Neutral);
    set_custom_stage_value(stage, 55, Road, Horizontal);
    set_custom_stage_value(stage, 56, Road, Horizontal);
    set_custom_stage_value(stage, 57, Road, Middle);
    set_custom_stage_value(stage, 58, Road, Horizontal);
    set_custom_stage_value(stage, 59, Road, Horizontal);

    set_custom_stage_value(stage, 67, Road, Vertical);

    set_custom_stage_value(stage, 77, Property_Base, Player_Index_1);

    return stage;
}
