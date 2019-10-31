#include <stdlib.h>

#include "conf.h"
#include "Game/Data/Palette/palette.h"

#define PALETTE_TEX_WIDTH  256
#define PALETTE_TEX_HEIGHT   1

// Apply a color to the given index of the given palette texture row.
void apply_palette_row_color(
    GLubyte palette_texture_row[PALETTE_TEX_WIDTH][4],
    int palette_index,
    GLubyte color[]
)
{
    palette_texture_row[palette_index][0] = color[0];
    palette_texture_row[palette_index][1] = color[1];
    palette_texture_row[palette_index][2] = color[2];
    palette_texture_row[palette_index][3] = 255;
}

// Apply palette colors in the JSON object to the given palette texture row.
void apply_palette_colors(GLubyte palette_texture_row[PALETTE_TEX_WIDTH][4], cJSON* palette_JSON)
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

GLuint create_palette_texture(cJSON* data_JSON)
{
    GLubyte palette_texture_data[PALETTE_TEX_HEIGHT][PALETTE_TEX_WIDTH][4];

    /*
    for (int i = 0; i < PALETTE_TEX_WIDTH; i++) {
        palette_texture_data[0][i][0] = (GLubyte)i;
        palette_texture_data[0][i][1] = (GLubyte)0;
        palette_texture_data[0][i][2] = (GLubyte)0;
        palette_texture_data[0][i][3] = (GLubyte)255;
    }
    */

    // Add unit palettes
    cJSON* units_JSON = cJSON_GetObjectItemCaseSensitive(data_JSON, "units");
    cJSON* units_palettes_JSON = cJSON_GetObjectItemCaseSensitive(units_JSON, "palettes");
    cJSON* units_base_palette_JSON = cJSON_GetObjectItemCaseSensitive(units_JSON, "basePalette");

    // OS
    cJSON* OS_palette_wrapper = cJSON_GetArrayItem(units_palettes_JSON, 0);
    cJSON* OS_palette = cJSON_GetObjectItemCaseSensitive(OS_palette_wrapper, "palette");

    apply_palette_colors(palette_texture_data[0], units_base_palette_JSON);
    apply_palette_colors(palette_texture_data[0], OS_palette);

    // BM
    /*
    cJSON* BM_palette_wrapper = cJSON_GetArrayItem(units_palettes_JSON, 1);
    cJSON* BM_palette = cJSON_GetObjectItemCaseSensitive(BM_palette_wrapper, "palette");

    apply_palette_colors(palette_texture_data[1], units_base_palette_JSON);
    apply_palette_colors(palette_texture_data[1], BM_palette);
*/
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
        PALETTE_TEX_HEIGHT, 
        0, 
        GL_RGBA, 
        GL_UNSIGNED_BYTE, 
        palette_texture_data
    );

    return texture;
}
