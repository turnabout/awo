#include <stdlib.h>
#include <cJSON.h>
#include <cglm/cglm.h>

#include "conf.h"
#include "Utilities/utilities.h"
#include "Game/Data/Palette/raw_palette.h"
#include "Game/_game.h"

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

Bool init_game_data(Game* game)
{
    // Load cJSON data object
    cJSON* data_JSON;

    if (!get_data_JSON(&data_JSON)) {
        return FALSE;
    }

    // Get the sprite sheet's dimensions
    cJSON* ss_dimensions_JSON = cJSON_GetObjectItemCaseSensitive(data_JSON, "ssDimensions");
    int sprite_sheet_w = cJSON_GetObjectItemCaseSensitive(ss_dimensions_JSON, "width")->valueint;
    int sprite_sheet_h = cJSON_GetObjectItemCaseSensitive(ss_dimensions_JSON, "height")->valueint;

    // Gather tiles data
    game->tiles_data = create_tiles_data(
        cJSON_GetObjectItemCaseSensitive(data_JSON, "tiles"),
        cJSON_GetObjectItemCaseSensitive(data_JSON, "properties"),
        sprite_sheet_w,
        sprite_sheet_h
    );

    // Gather units data
    game->units_data = create_units_data(
        cJSON_GetObjectItemCaseSensitive(data_JSON, "units"),
        sprite_sheet_w,
        sprite_sheet_h
    );

    // Get the raw palette data and store it
    game->raw_palette_texture = create_raw_palette_texture(
        cJSON_GetObjectItemCaseSensitive(data_JSON, "palettes")
    );

    // Create game clock
    game->clock = create_game_clock(
        cJSON_GetObjectItemCaseSensitive(data_JSON, "animationClocks"),
        &game->palette_texture
    );

    // Load all default stages
    cJSON* stages_array_JSON = cJSON_GetObjectItemCaseSensitive(data_JSON, "stages");

    for (int i = 0; i < MAX_LOADED_STAGE_COUNT; i++) {
        cJSON* stage_JSON = cJSON_GetArrayItem(stages_array_JSON, i);

        if (stage_JSON == NULL) {
            game->stages[i] = NULL;
            continue;
        }

        game->stages[i] = generate_stage_from_string(
            stage_JSON->valuestring,
            game->tiles_data
        );
    }

    // Delete parsed cJSON data object
    cJSON_Delete(data_JSON);

    return TRUE;
}
