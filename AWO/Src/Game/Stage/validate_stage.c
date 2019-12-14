#include "Game/Stage/_stage.h"

Bool validate_player_properties(Stage* stage)
{
    // TODO: gather counts of properties
    int prop_counts[MAX_PLAYER_COUNT][PROPERTY_TYPE_COUNT];
}

Bool validate_player_data(Stage* stage)
{
    // Validate player count
    if (stage->player_count < MIN_PLAYER_COUNT || stage->player_count > MAX_PLAYER_COUNT) {
        return FALSE;
    }

    int player_count;
    Bool end_reached = FALSE;
    for (player_count = 0; player_count < MAX_PLAYER_COUNT; player_count++) {

        // Should not find a player army after an ARMY_TYPE_NONE
        if (end_reached && stage->player_armies[player_count] != ARMY_TYPE_NONE) {
            return FALSE;
        }

        // Found the first ARMY_TYPE_NONE, check that player count matches
        if (stage->player_armies[player_count] == ARMY_TYPE_NONE) {
            end_reached = TRUE;

            if (player_count != stage->player_count) {
                return FALSE;
            }
        }
    }

    // Validate player armies are all different
    for (int i = 0; i < stage->player_count; i++) {
        if (i + 1 == stage->player_count) {
            break;
        }

        for (int j = i + 1; j < stage->player_count; j++) {
            if (stage->player_armies[i] == stage->player_armies[j]) {
                return FALSE;
            }
        }
    }

    return TRUE;
}

Bool validate_stage(Stage* stage)
{
    // Validate the player data (player count, property count, etc)
    validate_player_data(stage);


    return TRUE;
}
