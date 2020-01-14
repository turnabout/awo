#include "Game/Stage/_stage.h"

Bool validate_stage_string_data(Uint8* stage_data, size_t data_length, Tiles_Data* tiles_data)
{
    // Confirm amount of separators
    Uint8 sep_count = 0;

    for (size_t i = 0; i < data_length; i++) {
        if (stage_data[i] == STAGE_STRING_SEPARATOR_CHARACTER) {
            sep_count++;
        }
    }

    if (sep_count != VALID_SEPARATOR_COUNT) {
        return FALSE;
    }

    // Validate name
    int data_i = 0;

    while (1) {
        if (stage_data[data_i++] == STAGE_STRING_SEPARATOR_CHARACTER) {
            break;
        }
    }

    // Validate name length
    size_t name_length = 0;

    if (
        (name_length = (data_i - 1)) < STAGE_NAME_MIN_LENGTH || 
        name_length > STAGE_NAME_MAX_LENGTH
    ) {
        return FALSE;
    }

    // Validate players
    size_t player_count = 0;
    Uint8 player_armies_flags = 0;

    while (1) {

        Army_Type player_army = stage_data[data_i++];

        if (player_army == STAGE_STRING_SEPARATOR_CHARACTER) {
            break;
        }

        // Invalid player army
        if (player_army < ARMY_TYPE_FIRST || player_army > ARMY_TYPE_LAST) {
            return FALSE;
        }

        // Duplicate army
        if ((1 << player_army) & player_armies_flags) {
            return FALSE;
        }

        player_armies_flags |= (1 << player_army);
        player_count++;
    }

    // Validate player count
    if (player_count < MIN_PLAYER_COUNT || player_count > MAX_PLAYER_COUNT) {
        return FALSE;
    }

    // Validate stage dimensions
    size_t dimension_bytes_count = 0;
    data_i++; // Skip over separator

    while (1) {
        dimension_bytes_count++;

        if (stage_data[data_i] == STAGE_STRING_SEPARATOR_CHARACTER) {
            break;
        }

        data_i++;
    }
    
    if (dimension_bytes_count != 2) {
        return FALSE;
    }

    size_t stage_width = stage_data[data_i - 2];
    size_t stage_height = stage_data[data_i - 1];

    if (
        stage_width > STAGE_MAX_WIDTH ||
        stage_height > STAGE_MAX_HEIGHT ||
        (stage_width * stage_height) < STAGE_MIN_SURFACE
        ) {
        return FALSE;
    }

    // Validate tiles
    size_t tile_count = 0;

    data_i++;

    while (1) {
        if (
            stage_data[data_i] == STAGE_STRING_SEPARATOR_CHARACTER ||
            stage_data[data_i + 1] == STAGE_STRING_SEPARATOR_CHARACTER
            ) {
            break;
        }

        // Validate this tile exists
        Uint8 type = stage_data[data_i];
        Uint8 variation = stage_data[data_i + 1];

        if (type >= NEUTRAL_TILE_TYPE_FIRST && type <= NEUTRAL_TILE_TYPE_LAST) {

            // Validate neutral tile
            if (!tile_type_variation_exists(tiles_data, type, variation)) {
                return FALSE;
            }

        } else if (type >= PROPERTY_TILE_TYPE_FIRST && type <= PROPERTY_TILE_TYPE_LAST) {

            // Neutral HQs are invalid
            if (variation == Player_Index_Neutral) {
                if (type == HQ) {
                    return FALSE;
                }

            } else if (variation >= player_count) {
                // Player index invalid - out of bounds
                return FALSE;
            }

        } else {

            // Invalid tile type
            return FALSE;
        }

        data_i += 2;
        tile_count++;
    }

    // Validate tiles amount
    if (tile_count != (stage_width * stage_height)) {
        return FALSE;
    }
    
    return TRUE;
}
