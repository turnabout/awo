#pragma warning(disable: 6385)

#include <stdlib.h>

#include "conf.h"
#include "Game/Data/Palette/_palette.h"

typedef GLubyte Palette_Texture_Row[PALETTE_TEX_WIDTH][4];

// Apply a color to the given index of the given palette texture row.
void apply_palette_row_color(
    Palette_Texture_Row palette_texture_row,
    int palette_index,
    GLubyte color[4]
)
{
    palette_texture_row[palette_index][0] = color[0];
    palette_texture_row[palette_index][1] = color[1];
    palette_texture_row[palette_index][2] = color[2];
    palette_texture_row[palette_index][3] = 255;
}

// Apply palette colors in the JSON object to the given palette texture row.
void apply_palette_colors(Palette_Texture_Row palette_texture_row, cJSON* palette_JSON)
{
    // Apply colors from the palette
    cJSON* palette_item_JSON;
    cJSON_ArrayForEach(palette_item_JSON, palette_JSON)
    {
        apply_palette_row_color(
            palette_texture_row,

            (int)strtol(palette_item_JSON->string, (char**)NULL, 10),

            (GLubyte[]) { 
                cJSON_GetArrayItem(palette_item_JSON, 0)->valueint,
                cJSON_GetArrayItem(palette_item_JSON, 1)->valueint,
                cJSON_GetArrayItem(palette_item_JSON, 2)->valueint 
            }
        );
    }
}

GLuint create_palette_texture(cJSON* palette_data_JSON)
{
    cJSON* base_palettes_JSON = cJSON_GetObjectItemCaseSensitive(palette_data_JSON, "basePalettes");
    cJSON* palettes_JSON = cJSON_GetObjectItemCaseSensitive(palette_data_JSON, "palettes");

    int palette_count = cJSON_GetArraySize(palettes_JSON);

    Palette_Texture_Row* palette_texture_data = malloc(sizeof(Palette_Texture_Row) * palette_count);

    // Add unit palettes
    cJSON* units_base_palette = cJSON_GetObjectItemCaseSensitive(base_palettes_JSON, "units");
    cJSON* tiles_base_palette = cJSON_GetObjectItemCaseSensitive(base_palettes_JSON, "tiles");
    cJSON* props_base_palette = cJSON_GetObjectItemCaseSensitive(base_palettes_JSON, "properties");

    for (int j = 0; j < palette_count; j++) {
        for (int i = 0; i < PALETTE_TEX_WIDTH; i++) {
            palette_texture_data[j][i][0] = (GLubyte)0;
            palette_texture_data[j][i][1] = (GLubyte)0;
            palette_texture_data[j][i][2] = (GLubyte)0;
            palette_texture_data[j][i][3] = (GLubyte)255;
        }
    }

    for (int i = 0; i < palette_count; i++) {
        // Get appropriate base palette
        cJSON* base_palette;

        if (i <= UNIT_VAR_LAST) {
            base_palette = units_base_palette;
        } else if (i <= UNIT_VAR_LAST + WEATHER_LAST) {
            base_palette = tiles_base_palette;
        } else {
            base_palette = props_base_palette;
        }

        // Apply palettes
        apply_palette_colors(palette_texture_data[i], base_palette);
        apply_palette_colors(palette_texture_data[i], cJSON_GetArrayItem(palettes_JSON, i));
    }

    init_palette_NDC_indexes(palette_count);

    // Create the texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(
        GL_TEXTURE_2D, 
        0, 
        GL_RGBA, 
        PALETTE_TEX_WIDTH, 
        palette_count, 
        0, 
        GL_RGBA, 
        GL_UNSIGNED_BYTE, 
        palette_texture_data
    );

    free(palette_texture_data);

    return texture;
}
