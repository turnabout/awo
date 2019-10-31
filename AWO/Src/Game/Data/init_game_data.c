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

int init_game_data(Game* game)
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

    // Set sprite sheet projection matrix. Used to transform sprites' x/y/w/h coordinates into
    // Normalized Device Coordinates usable by OpenGL.
    mat4 projection;
    glm_ortho(0.0f, (float)sprite_sheet_w, 0.0f, (float)sprite_sheet_h, -1.0f, 1.0f, projection);

    // Gather units data
    game->units_data = create_units_data(
        cJSON_GetObjectItemCaseSensitive(data_JSON, "units"),
        projection
    );

    // Gather tiles data
    game->tiles_data = create_tiles_data(
        cJSON_GetObjectItemCaseSensitive(data_JSON, "tiles"),
        projection
    );

    // Use palette data to create palette color map texture
    game->palette_texture = create_palette_texture(data_JSON);

    // Create game clock
    game->clock = create_game_clock(
        cJSON_GetObjectItemCaseSensitive(data_JSON, "animationClocks")
    );

    // Delete parsed cJSON data object
    cJSON_Delete(data_JSON);

    return 1;
}
