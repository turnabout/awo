#include <stdio.h>
#include <stdlib.h>

#include "Game/Stage/_stage.h"

void write_stage_string_byte(char* stage_string, Uint8 byte, int* i)
{
    static const Uint8* hex = "0123456789ABCDEF";

    stage_string[*i] = hex[(byte >> 4) & 0xF];
    stage_string[*i + 1] = hex[byte & 0xF];

    (*i) += 2;
}

void write_stage_string_name(Stage* stage, char* stage_string, int* i, int name_char_count)
{
    // Write the stage name
    for (int j = 0; j < name_char_count; j++) {
        write_stage_string_byte(stage_string, stage->name[j], i);
    }

    write_stage_string_byte(stage_string, STAGE_STRING_SEPARATOR_CHARACTER, i);
}

void write_stage_string_player_data(Stage* stage, char* stage_string, int* i)
{
    // Write the player armies
    for (int j = 0; j < stage->player_count; j++) {
        write_stage_string_byte(stage_string, stage->player_armies[j], i);
    }

    write_stage_string_byte(stage_string, STAGE_STRING_SEPARATOR_CHARACTER, i);
}

void write_stage_string_tiles(Stage* stage, char* stage_string, int* i)
{
    for (Uint8 y = 0; y < stage->height; y++) {
        for (Uint8 x = 0; x < stage->width; x++) {
            write_stage_string_byte(stage_string, stage->tiles_grid[y][x].type, i);
            write_stage_string_byte(stage_string, stage->tiles_grid[y][x].variation, i);
        }
    }

    write_stage_string_byte(stage_string, STAGE_STRING_SEPARATOR_CHARACTER, i);
}

char* stringify_stage(Stage* stage)
{
    // Validate the stage before stringifying
    if (!validate_stage(stage)) {
        return NULL;
    }

    // Get stage name character count (without null-terminator)
    int name_char_count;

    for (name_char_count = 0; name_char_count < STAGE_NAME_MAX_LENGTH; name_char_count++) {
        if (stage->name[name_char_count] == '\0') {
            break;
        }
    }

    // Allocate the buffer
    char* stage_string = malloc(
        (2 * VALID_SEPARATOR_COUNT) +          // Separators
        (2 * name_char_count) +                // Stage name
        (2 * stage->player_count) +            // Player data
        (2 * 2) +                              // Dimensions
        (4 * (stage->width * stage->height)) + // Tiles
        1                                      // Null terminator
    );

    int i = 0;

    // Write the stage name
    write_stage_string_name(stage, stage_string, &i, name_char_count);

    // Write the player data
    write_stage_string_player_data(stage, stage_string, &i);

    // Write the stage dimensions
    write_stage_string_byte(stage_string, stage->width, &i);
    write_stage_string_byte(stage_string, stage->height, &i);
    write_stage_string_byte(stage_string, STAGE_STRING_SEPARATOR_CHARACTER, &i);

    // Write the stage tiles
    write_stage_string_tiles(stage, stage_string, &i);
    stage_string[i] = '\0';

    return stage_string;
}