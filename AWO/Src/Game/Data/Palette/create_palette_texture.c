#pragma warning(disable: 6385)

#include <stdlib.h>
#include <string.h>

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

GLuint create_palette_texture(cJSON* palettes_JSON)
{
    // cJSON* palettes_JSON = cJSON_GetObjectItemCaseSensitive(palette_data_JSON, "palettes");
    int palette_count = cJSON_GetArraySize(palettes_JSON);
    
    Palette_Texture_Row* palette_texture_data = malloc(sizeof(Palette_Texture_Row) * palette_count);

    for (int i = 0; i < palette_count; i++) {
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
