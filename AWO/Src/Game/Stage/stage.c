#include <stdlib.h>

#include "Game/Stage/_stage.h"
#include "Utilities/utilities.h"

Stage* load_stage(char* stage_str, Tiles_Data* tiles_data)
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
    Stage* stage = malloc(sizeof(Stage));

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

    // Point index to after the separator
    i += 3;

    // Process stage tiles
    allocate_stage_grid(stage);

    for (Uint8 y = 0; y < stage->height; y++) {
        for (Uint8 x = 0; x < stage->width; x++) {
            edit_stage_tile(stage, x, y, stage_data[i], stage_data[i + 1]);
            i += 2;
        }
    }

    return stage;
}

void allocate_stage_grid(Stage* stage)
{
    stage->tiles_grid = malloc(sizeof(Stage_Tile_Row) * stage->height);

    for (Uint8 y = 0; y < stage->height; y++) {
        stage->tiles_grid[y] = malloc(sizeof(Stage_Tile) * stage->width);
    }
}


void edit_stage_tile(Stage* stage, int x, int y, int type, int variation)
{
    stage->tiles_grid[y][x].type = type;
    stage->tiles_grid[y][x].variation = variation;
}

void fill_stage_tiles(Stage* stage, int type, int variation)
{
    for (Uint8 y = 0; y < stage->height; y++) {
        for (Uint8 x = 0; x < stage->width; x++) {
            edit_stage_tile(stage, x, y, type, variation);
        }
    }
}

void free_stage(Stage* stage)
{
    if (stage == NULL) {
        return;
    }

    if (stage->tiles_grid != NULL) {

        for (int y = 0; y < stage->height; y++) {
            if (stage->tiles_grid[y] != NULL) {
                free(stage->tiles_grid[y]);
            }
        }

        free(stage->tiles_grid);
    }

    free(stage);
}