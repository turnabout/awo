#include <stdio.h>

#include "Stage/_stage.h"

// PRAGMA( warning( disable: 6385 ) )

Bool validate_stage_tiles(Stage* stage)
{
    // Add array to keep track of property counts
    int prop_counts[MAX_PLAYER_COUNT][PROPERTY_TYPE_COUNT];

    // Start counts at 0
    for (int player = 0; player < stage->player_count; player++) {
        for (Property_Type type = PROPERTY_TYPE_FIRST; type < PROPERTY_TYPE_COUNT; type++) {
            prop_counts[player][type] = 0;
        }
    }

    for (Uint8 y = 0; y < stage->height; y++) {
        for (Uint8 x = 0; x < stage->width; x++) {

            Tile_Type type = stage->tiles_grid[y][x].type;
            int variation = stage->tiles_grid[y][x].variation;

            if (type >= NEUTRAL_TILE_TYPE_FIRST && type <= NEUTRAL_TILE_TYPE_LAST) {
            } else if (type >= PROPERTY_TILE_TYPE_FIRST && type <= PROPERTY_TILE_TYPE_LAST) {

                // No need to record neutral army property
                if (variation == Player_Index_Neutral) {

                    // Neutral HQs are invalid
                    if (type == HQ) {
                        printf("Neutral HQs are invalid\n");
                        return FALSE;
                    }

                    continue;
                }

                // Player index invalid - out of bounds (and not neutral)
                if (variation >= stage->player_count) {
                    printf(
                        "Property tile: found player index %d out of bounds (%d)\n", 
                        variation, 
                        stage->player_count
                    );
                    return FALSE;
                }

                // Record the property in the counts
                prop_counts[variation][type - PROPERTY_TILE_TYPE_FIRST]++;

            } else {

                // Invalid tile type
                printf("Tile: invalid type %d\n", type);
                return FALSE;
            }
        }
    }

    // Validate property counts
    for (int player = 0; player < stage->player_count; player++) {
        if (prop_counts[player][HQ] != HQS_PER_ARMY) {
            printf("Found %d HQs for player index %d\n", prop_counts[player][HQ], player);
            return FALSE;
        }

        int total_player_props_count = 0;

        for (Property_Type type = PROPERTY_TYPE_FIRST; type < PROPERTY_TYPE_COUNT; type++) {
            total_player_props_count++;
        }

        if (total_player_props_count > MAX_PROPERTIES_PER_PLAYER) {
            printf(
                "Property count for player %d exceeds limit (%d higher than %d)\n",
                player,
                total_player_props_count,
                MAX_PROPERTIES_PER_PLAYER
            );
            return FALSE;
        }
    }

    return TRUE;
}

Bool validate_stage_player_data(Stage* stage)
{
    // Validate player count
    if (stage->player_count < MIN_PLAYER_COUNT || stage->player_count > MAX_PLAYER_COUNT) {
        printf("Player count wrong: %d\n", stage->player_count);
        return FALSE;
    }

    Uint8 player_count;
    Bool last_reached = FALSE;
    for (player_count = 0; player_count < MAX_PLAYER_COUNT; player_count++) {

        // Should not find a player army after an ARMY_TYPE_NONE
        if (last_reached && stage->player_armies[player_count] != ARMY_TYPE_NONE) {
            printf("Found player army after an ARMY_TYPE_NONE at index %d\n", player_count);
            return FALSE;
        }

        // Found the first ARMY_TYPE_NONE, check that player count matches
        if (stage->player_armies[player_count] == ARMY_TYPE_NONE && !last_reached) {
            last_reached = TRUE;

            if (player_count != stage->player_count) {
                printf("player counts don't match: %d and %d\n", stage->player_count, player_count);
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
                printf("player armies are same: %d and %d\n", stage->player_armies[i], stage->player_armies[j]);
                return FALSE;
            }
        }
    }

    return TRUE;
}

Bool validate_stage(Stage* stage)
{
    return (validate_stage_player_data(stage) && validate_stage_tiles(stage));
}
