#include <stdlib.h>

#include "Game/Stage/_stage_descriptor.h"
#include "Utilities/utilities.h"

Stage_Descriptor* load_stage_descriptor(char* stage_str, Tiles_Data* tiles_data)
{
    // Translate the hex string into a useable data bytes array & validate
    Uint8* stage_data;
    size_t data_length;
 
    if ((stage_data = hex_string_to_data(stage_str, &data_length)) == NULL || 
         !validate_stage_data(stage_data, data_length, tiles_data)
    ) {
        free(stage_str);
        return NULL;
    }

    // Create the stage descriptor, populate & return
    Stage_Descriptor* stage = (Stage_Descriptor*)malloc(sizeof(Stage_Descriptor));

    // Process data byte array
    size_t i = 0;

    // Process name
    while (1) {
        if (stage_data[i] == STAGE_STRING_SEPARATOR_CHARACTER) {
            stage->name[i] = '\0';
            i++;
            break;
        }

        stage->name[i] = stage_data[i];
        i++;
    }

    // Process players data
    stage->player_count = 0;

    while (1) {

        Army_Type player_army = stage_data[i++];

        if (player_army == STAGE_STRING_SEPARATOR_CHARACTER) {
            break;
        }

        stage->player_armies[stage->player_count] = player_army;
        stage->player_count++;
    }

    // Initialize other player armies to NONE
    for (int j = stage->player_count; j < MAX_PLAYER_COUNT; j++) {
        stage->player_armies[j] = ARMY_TYPE_NONE;
    }

    // Process stage dimensions
    stage->width = stage_data[i];
    stage->height = stage_data[i + 1];
    stage->tile_count = stage->width * stage->height;

    // Point index to after the separator
    i += 3;

    // Process stage tiles
    stage->tile_descriptors = (Tile_Descriptor*)malloc(
        sizeof(Tile_Descriptor) * stage->tile_count
    );

    int tile_n = 0;

    while (1) {
        if (
            stage_data[i] == STAGE_STRING_SEPARATOR_CHARACTER ||
            stage_data[i + 1] == STAGE_STRING_SEPARATOR_CHARACTER
            ) {
            break;
        }

        stage->tile_descriptors[tile_n].type = (Tile_Type)stage_data[i];
        stage->tile_descriptors[tile_n].variation = (Tile_Variation)stage_data[i + 1];

        i += 2;
        tile_n++;
    }

    return stage;
}

void free_stage_descriptor(Stage_Descriptor* stage_descriptor)
{
    free(stage_descriptor->tile_descriptors);
    free(stage_descriptor);
}