#include <stdlib.h>
#include <string.h>

#include "Include/emx.h"
#include "Config/config.h"
#include "Utilities/utilities.h"
#include "Game_Data/game_data.h"
#include "Game_Message/game_message.h"
#include "GL_Helpers/gl_helpers.h"

Bool get_data_JSON(cJSON **data_JSON)
{
    // Get file contents & size
    char *JSON_file_contents;

    if ((JSON_file_contents = read_file(GAME_DATA_JSON_PATH)) == NULL) {
        return FALSE;
    }

    // Populate visuals JSON struct
    *data_JSON = cJSON_Parse(JSON_file_contents);

    // Clear previously allocated file contents
    free(JSON_file_contents);

    return TRUE;
}

Game_Data* EMX create_game_data()
{
    Game_Data* data = malloc(sizeof(Game_Data));

    // Store sprite sheet texture on game
    data->sprite_sheet = create_sprite_sheet_data();

    int ss_width, ss_height;
    get_sprite_sheet_dimensions(data->sprite_sheet, &ss_width, &ss_height);

    // Load cJSON data object
    cJSON* data_JSON;

    if (!get_data_JSON(&data_JSON)) {
        printe("Error getting data JSON");
        return NULL;
    }

    // Gather tiles data
    data->tile = create_tile_data(
        cJSON_GetObjectItem(data_JSON, "tiles"),
        ss_width,
        ss_height
    );

    data->property = create_property_tiles_data(
        cJSON_GetObjectItem(data_JSON, "properties"),
        ss_width,
        ss_height
    );

    // Gather units data
    data->unit = create_unit_data(
        cJSON_GetObjectItem(data_JSON, "units"),
        ss_width,
        ss_height
    );

    // Gather UI data
    data->UI = create_UI_data(
        cJSON_GetObjectItem(data_JSON, "ui"),
        ss_width,
        ss_height
    );

    // Gather CO data
    data->CO = create_CO_data(
        cJSON_GetObjectItem(data_JSON, "COs"),
        ss_width,
        ss_height
    );

    // Gather clock data
    data->clock = create_clock_data(
        cJSON_GetObjectItem(data_JSON, "clocks")
    );

    // Get the raw palette data and store it
    data->palette = create_palette_data(
        cJSON_GetObjectItem(data_JSON, "palettes")
    );

    // Confirm all modules were initialized successfully
    if (
        data->tile == NULL ||
        data->property == NULL ||
        data->unit == NULL ||
        data->UI== NULL ||
        data->CO== NULL ||
        data->clock== NULL ||
        data->palette == NULL ||
        data->sprite_sheet == NULL
    ) {
        free_game_data(data);
        printe("Game data: one more more modules were not initialized successfully");
        return NULL;
    }

    // Get all default stages strings
    cJSON* stages_array_JSON = cJSON_GetObjectItem(data_JSON, "stages");

    for (int i = 0; i < MAX_LOADED_STAGE_COUNT; i++) {
        cJSON* stage_JSON = cJSON_GetArrayItem(stages_array_JSON, i);

        if (stage_JSON == NULL) {
            data->default_stages[i] = NULL;
            continue;
        }

        size_t stage_str_len = strlen(stage_JSON->valuestring) + 1;
        data->default_stages[i] = malloc(stage_str_len);
        strcpy_s(data->default_stages[i], stage_str_len, stage_JSON->valuestring);
    }

    // Delete parsed cJSON data object
    cJSON_Delete(data_JSON);
    return data;
}

void EMX free_game_data(Game_Data* data)
{
    if (data == NULL) {
        return;
    }

    free_tile_data(data->tile);
    free_units_data(data->unit);
    free_UI_data(data->UI);
    free_CO_data(data->CO);
    free_clock_data(data->clock);

    for (int i = 0; i < MAX_LOADED_STAGE_COUNT; i++) {
        free(data->default_stages[i]);
    }

    free(data);
}