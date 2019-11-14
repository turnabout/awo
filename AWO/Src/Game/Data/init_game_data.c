#include <stdlib.h>
#include <cJSON.h>
#include <cglm/cglm.h>

#include "conf.h"
#include "Utilities/utilities.h"
#include "Game/Data/Palette/palette.h"
#include "Game/_game.h"

int get_data_JSON(const cJSON **data_JSON)
{
    // Get file contents & size
    char *JSON_file_contents;

    if ((JSON_file_contents = read_file(GAME_DATA_JSON_PATH)) == NULL) {
        return 0;
    }

    // Populate visuals JSON struct
    *data_JSON = cJSON_Parse(JSON_file_contents);

    // Clear previously allocated file contents
    free(JSON_file_contents);

    return 1;
}

int init_game_data(Game* game, int stage_index)
{
    // Load cJSON data object
    cJSON* data_JSON;

    if (!get_data_JSON(&data_JSON)) {
        return 0;
    }

    // Get the sprite sheet's dimensions
    cJSON* ss_dimensions_JSON = cJSON_GetObjectItemCaseSensitive(data_JSON, "ssDimensions");
    int sprite_sheet_w = cJSON_GetObjectItemCaseSensitive(ss_dimensions_JSON, "width")->valueint;
    int sprite_sheet_h = cJSON_GetObjectItemCaseSensitive(ss_dimensions_JSON, "height")->valueint;

    // Gather units data
    game->units_data = create_units_data(
        cJSON_GetObjectItemCaseSensitive(data_JSON, "units"),
        sprite_sheet_w,
        sprite_sheet_h
    );

    // Gather tiles data
    game->tiles_data = create_tiles_data(
        cJSON_GetObjectItemCaseSensitive(data_JSON, "tiles"),
        sprite_sheet_w,
        sprite_sheet_h
    );

    // Use palette data to create palette color hashmap texture
    game->palettes_texture = create_palette_texture(
        cJSON_GetObjectItemCaseSensitive(data_JSON, "palettes")
    );

    // Create game clock
    game->clock = create_game_clock(
        cJSON_GetObjectItemCaseSensitive(data_JSON, "animationClocks")
    );

    // Attach string of the stage to load
    cJSON* stages_array_JSON = cJSON_GetObjectItemCaseSensitive(data_JSON, "stages");
    cJSON* stage_JSON = cJSON_GetArrayItem(stages_array_JSON, stage_index);

    game->stage_str = stage_JSON->valuestring;

    // Detach valuestring of the loaded stage to prevent cJSON_Delete from deleting it
    stage_JSON->valuestring = NULL;

    // Delete parsed cJSON data object
    cJSON_Delete(data_JSON);

    return 1;
}
