#include <stdio.h>
#include <stdlib.h>

#include "Game/Stage/_stage.h"

void write_stage_string_byte(char* stage_string, char byte, int* i)
{
    static const char* hex = "0123456789ABCDEF";

    stage_string[*i] = hex[(byte >> 4) & 0xF];
    stage_string[*i + 1] = hex[byte & 0xF];

    (*i) += 2;
}

void write_stage_string_name(Stage* stage, int name_char_count, char* stage_string, int* i)
{
    // Write the stage name
    for (int j = 0; j < name_char_count; j++) {
        write_stage_string_byte(stage_string, stage->name[j], i);
    }

    // Write separator after stage name
    write_stage_string_byte(stage_string, STAGE_STRING_SEPARATOR_CHARACTER, i);
}

char* stringify_stage(Stage* stage)
{
    // TODO: validate the stage before stringifying

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
    write_stage_string_name(stage, name_char_count, stage_string, &i);
    stage_string[i] = '\0';

    // Write the player armies

    // Write the stage dimensions

    // Write the stage tiles

    // name                pyrs    w/h     tiles
    // 4D79205374616765 FF 0004 FF 010A FF 000000000604060C060C060C060C060502000100 FF

    return stage_string;
}