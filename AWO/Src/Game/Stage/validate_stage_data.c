#include "Game/Stage/_stage_descriptor.h"

Bool validate_stage_data(Uint8* stage_data, size_t data_length, Tiles_Data* tiles_data)
{
    // Confirm there are 3 separators
    Uint8 sep_count = 0;

    for (size_t i = 0; i < data_length; i++) {
        if (stage_data[i] == STAGE_STRING_SEPARATOR_CHARACTER) {
            sep_count++;
        }
    }

    if (sep_count != 3) {
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

    // Validate stage dimensions
    size_t dimension_bytes_count = 0;
    data_i++;

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
        if (!tile_type_variation_exists(tiles_data, stage_data[data_i], stage_data[data_i + 1])) {
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
