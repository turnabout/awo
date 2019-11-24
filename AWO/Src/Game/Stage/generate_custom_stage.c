#include <string.h>
#include <stdlib.h>

#include "Game/Stage/_stage.h"
#include "Game/Player/player_index_enum.h"
#include "Utilities/utilities.h"

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
    stage->tiles[stage->tile_count - 1].type = Property_HQ;
    stage->tiles[stage->tile_count - 1].variation = Player_Index_0;

    stage->tiles[stage->tile_count - 2].type = Property_HQ;
    stage->tiles[stage->tile_count - 2].variation = Player_Index_1;

    stage->tiles[0].type = Property_City;
    stage->tiles[0].variation = Player_Index_0;

    stage->tiles[1].type = Property_Airport;
    stage->tiles[1].variation = Player_Index_0;

    stage->tiles[2].type = Property_Port;
    stage->tiles[2].variation = Player_Index_0;

    stage->tiles[21].type = Property_Base;
    stage->tiles[21].variation = Player_Index_0;

    // Sea test
    stage->tiles[23].type = Sea;
    stage->tiles[23].variation = TopLeft;
    stage->tiles[24].type = Sea;
    stage->tiles[24].variation = Top;
    stage->tiles[25].type = Sea;
    stage->tiles[25].variation = TopRight;

    stage->tiles[33].type = Sea;
    stage->tiles[33].variation = DirLeft;
    stage->tiles[34].type = Sea;
    stage->tiles[34].variation = Middle;
    stage->tiles[35].type = Sea;
    stage->tiles[35].variation = DirRight;

    stage->tiles[43].type = Sea;
    stage->tiles[43].variation = BottomLeft;
    stage->tiles[44].type = Sea;
    stage->tiles[44].variation = Bottom;
    stage->tiles[45].type = Sea;
    stage->tiles[45].variation = BottomRight;

    return stage;
}
