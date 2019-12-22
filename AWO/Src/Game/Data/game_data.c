#include <stdlib.h>

#include "conf.h"
#include "Utilities/utilities.h"
#include "GL_Helpers/gl_helpers.h"
#include "Game/Data/game_data.h"

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
    int ss_texture_w, ss_texture_h;
    data->sprite_sheet = create_texture_object(SPRITE_SHEET_PATH, &ss_texture_w, &ss_texture_h);

    // Load cJSON data object
    cJSON* data_JSON;

    if (!get_data_JSON(&data_JSON)) {
        return FALSE;
    }

    // Gather tiles data
    data->tiles_data = create_tiles_data(
        cJSON_GetObjectItemCaseSensitive(data_JSON, "tiles"),
        cJSON_GetObjectItemCaseSensitive(data_JSON, "properties"),
        ss_texture_w,
        ss_texture_h
    );

    // Gather units data
    data->units_data = create_units_data(
        cJSON_GetObjectItemCaseSensitive(data_JSON, "units"),
        ss_texture_w,
        ss_texture_h
    );

    // Gather UI data
    data->UI_data = create_UI_data(
        cJSON_GetObjectItemCaseSensitive(data_JSON, "ui"),
        ss_texture_w,
        ss_texture_h
    );

    // Gather CO data
    data->CO_data = create_CO_data(
        cJSON_GetObjectItemCaseSensitive(data_JSON, "COs"),
        ss_texture_w,
        ss_texture_h
    );

    // Gather clock data
    data->clock_data = create_clock_data(
        cJSON_GetObjectItemCaseSensitive(data_JSON, "animationClocks")
    );

    // Get the raw palette data and store it
    data->raw_palette = create_raw_palette_texture(
        cJSON_GetObjectItemCaseSensitive(data_JSON, "palettes")
    );

    // Load all default stages
    cJSON* stages_array_JSON = cJSON_GetObjectItemCaseSensitive(data_JSON, "stages");

    for (int i = 0; i < MAX_LOADED_STAGE_COUNT; i++) {
        cJSON* stage_JSON = cJSON_GetArrayItem(stages_array_JSON, i);

        if (stage_JSON == NULL) {
            data->stages[i] = NULL;
            continue;
        }

        data->stages[i] = generate_stage_from_string(
            stage_JSON->valuestring,
            data->tiles_data
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

    free_tiles_data(data->tiles_data);
    free_units_data(data->units_data);
    free_UI_data(data->UI_data);
    free_CO_data(data->CO_data);
    free_clock_data(data->clock_data);

    for (int i = 0; i < MAX_LOADED_STAGE_COUNT; i++) {
        free_stage(data->stages[i]);
    }

    free(data);
}