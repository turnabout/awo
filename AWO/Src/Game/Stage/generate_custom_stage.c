#include <string.h>
#include <stdlib.h>

#include "Game/Stage/_stage.h"
#include "Game/Player/player_index_enum.h"
#include "Utilities/utilities.h"

Stage* generate_custom_stage()
{
    Stage* stage = create_stage(
        "Custom stage",
        10,
        10,
        (Army_Type[MAX_PLAYER_COUNT]){OS, GE, ARMY_TYPE_NONE, ARMY_TYPE_NONE}
    );

    // Add default tiles
    fill_stage_tiles(stage, Plain, Default);

    // Some properties
    edit_stage_tile(stage, 0, 0, Property_City, Player_Index_0);
    edit_stage_tile(stage, 1, 0, Property_Airport, Player_Index_0);
    edit_stage_tile(stage, 2, 0, Property_Port, Player_Index_0);
    edit_stage_tile(stage, 3, 0, Property_HQ, Player_Index_0);
    edit_stage_tile(stage, 9, 9, Property_HQ, Player_Index_1);

    edit_stage_tile(stage, 1, 2, Property_Base, Player_Index_0);

    // Sea
    edit_stage_tile(stage, 3, 2, Sea, TopLeft);
    edit_stage_tile(stage, 4, 2, Sea, Top);
    edit_stage_tile(stage, 5, 2, Sea, TopRight);

    edit_stage_tile(stage, 3, 3, Sea, Left);
    edit_stage_tile(stage, 4, 3, Sea, Middle);
    edit_stage_tile(stage, 5, 3, Sea, Right);

    edit_stage_tile(stage, 3, 4, Sea, BottomLeft);
    edit_stage_tile(stage, 4, 4, Sea, Bottom);
    edit_stage_tile(stage, 5, 4, Sea, BottomRight);

    // Some roads & properties
    edit_stage_tile(stage, 7, 2, Road, TopLeft);
    edit_stage_tile(stage, 8, 2, Road, Horizontal);
    edit_stage_tile(stage, 9, 2, Road, Horizontal);

    edit_stage_tile(stage, 8, 3, Forest, TopLeft);
    edit_stage_tile(stage, 9, 3, Forest, TopRight);
    edit_stage_tile(stage, 8, 4, Forest, BottomLeft);
    edit_stage_tile(stage, 9, 4, Forest, BottomRight);

    edit_stage_tile(stage, 7, 3, Road, Vertical);
    edit_stage_tile(stage, 7, 4, Road, Vertical);

    edit_stage_tile(stage, 3, 5, Silo, Default);
    edit_stage_tile(stage, 4, 5, Property_City, Player_Index_Neutral);
    edit_stage_tile(stage, 5, 5, Road, Horizontal);
    edit_stage_tile(stage, 6, 5, Road, Horizontal);
    edit_stage_tile(stage, 7, 5, Road, Middle);
    edit_stage_tile(stage, 8, 5, Road, Horizontal);
    edit_stage_tile(stage, 9, 5, Road, Horizontal);

    edit_stage_tile(stage, 7, 6, Road, Vertical);

    edit_stage_tile(stage, 7, 7, Property_Base, Player_Index_1);

    return stage;
}
