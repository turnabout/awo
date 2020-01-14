#include <stdlib.h>

#include "Utilities/utilities.h"
#include "Stage/_stage.h"

Stage* create_stage(
    char* stage_name,
    Uint8 width,
    Uint8 height,
    Army_Type player_armies[MAX_PLAYER_COUNT]
)
{
    Stage* stage = malloc(sizeof(Stage));

    if (stage == NULL) {
        return NULL;
    }

    stage->width = width;
    stage->height = height;
    stage->tiles_grid = NULL;
    stage->player_count = 0;

    // Copy name
    for (int i = 0; i < STAGE_NAME_MAX_LENGTH; i++) {
        if (stage_name[i] == '\0') {
            stage->name[i] = '\0';
            break;
        }

        stage->name[i] = stage_name[i];
    }

    stage->name[STAGE_NAME_MAX_LENGTH - 1] = '\0';

    // Fill out armies with default data
    for (int i = 0; i < MAX_PLAYER_COUNT; i++) {
        stage->player_armies[i] = ARMY_TYPE_NONE;
    }

    // Copy armies
    for (stage->player_count = 0; stage->player_count < MAX_PLAYER_COUNT; stage->player_count++) {
        if (player_armies[stage->player_count] == ARMY_TYPE_NONE) {
            break;
        }

        stage->player_armies[stage->player_count] = player_armies[stage->player_count];
    }

    // Allocate space for tile grid
    stage->tiles_grid = malloc(sizeof(Stage_Tile_Row) * stage->height);

    if (stage->tiles_grid == NULL) {
        free_stage(stage);
        return NULL;
    }

    for (Uint8 y = 0; y < stage->height; y++) {
        stage->tiles_grid[y] = malloc(sizeof(Stage_Tile) * stage->width);
    }

    return stage;
}

void inline edit_stage_tile(Stage* stage, int x, int y, int type, int variation)
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