#include <stdlib.h>

#include "Config/config.h"
#include "Utilities/utilities.h"
#include "Game_Data/game_data.h"
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

Game_Data* create_game_data()
{
    Game_Data* data = malloc(sizeof(Game_Data));

    // Store sprite sheet texture on game
    data->sprite_sheet = create_texture_object(
        SPRITE_SHEET_PATH, 
        &data->sprite_sheet_width, 
        &data->sprite_sheet_height
    );

    // Load cJSON data object
    cJSON* data_JSON;

    if (!get_data_JSON(&data_JSON)) {
        // printe("Error getting data JSON");
        return NULL;
    }

    // Gather tiles data
    data->tile = create_tile_data(
        cJSON_GetObjectItem(data_JSON, "tiles"),
        data->sprite_sheet_width,
        data->sprite_sheet_height
    );

    data->property = create_property_tiles_data(
        cJSON_GetObjectItem(data_JSON, "properties"),
        data->sprite_sheet_width,
        data->sprite_sheet_height
    );

    // Gather units data
    data->unit = create_unit_data(
        cJSON_GetObjectItem(data_JSON, "units"),
        data->sprite_sheet_width,
        data->sprite_sheet_height
    );

    // Gather UI data
    data->UI = create_UI_data(
        cJSON_GetObjectItem(data_JSON, "ui"),
        data->sprite_sheet_width,
        data->sprite_sheet_height
    );

    // Gather CO data
    data->CO = create_CO_data(
        cJSON_GetObjectItem(data_JSON, "COs"),
        data->sprite_sheet_width,
        data->sprite_sheet_height
    );

    // Gather clock data
    data->clock = create_clock_data(
        cJSON_GetObjectItem(data_JSON, "clocks")
    );

    // Get the raw palette data and store it
    data->palette = create_palette_data(
        cJSON_GetObjectItem(data_JSON, "palettes")
    );

    // Load all default stages
    cJSON* stages_array_JSON = cJSON_GetObjectItem(data_JSON, "stages");

    for (int i = 0; i < MAX_LOADED_STAGE_COUNT; i++) {
        cJSON* stage_JSON = cJSON_GetArrayItem(stages_array_JSON, i);

        if (stage_JSON == NULL) {
            data->default_stages[i] = NULL;
            continue;
        }

        data->default_stages[i] = generate_stage_from_string(
            stage_JSON->valuestring,
            data->tile
        );
    }

    // Delete parsed cJSON data object
    cJSON_Delete(data_JSON);
    return data;
}

void free_game_data(Game_Data* data)
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
        free_stage(data->default_stages[i]);
    }

    free(data);
}