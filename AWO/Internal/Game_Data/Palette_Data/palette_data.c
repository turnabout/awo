#pragma once

#include <stdlib.h>
#include <string.h>

#include "Game_Data/Palette_Data/_palette_data.h"

// Apply a color to the given index of the given palette texture row.
void apply_palette_row_color(
    Palette_Data_Row palette_texture_row,
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
void apply_palette_colors(Palette_Data_Row palette_texture_row, cJSON* palette_JSON)
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

Palette_Data* create_palette_data(cJSON* palette_JSON)
{
    Palette_Data* palette_data = malloc(sizeof(Palette_Data));

    if (palette_data == NULL) {
        return NULL;
    }

    palette_data->buffer = NULL;
    // palette_data->texture = 0;

    // Allocate memory for the palette data rows & fill out using JSON data
    int palette_count = cJSON_GetArraySize(palette_JSON);

    palette_data->buffer = malloc(sizeof(Palette_Data_Row) * palette_count);

    if (palette_data->buffer == NULL) {
        free_palette_data(palette_data);
        return NULL;
    }

    memset(palette_data->buffer, 0, sizeof(Palette_Data_Row) * palette_count);

    for (int i = 0; i < palette_count; i++) {
        apply_palette_colors(palette_data->buffer[i], cJSON_GetArrayItem(palette_JSON, i));
    }

    // Create the texture
    /*
    glGenTextures(1, &palette_data->texture);
    glBindTexture(GL_TEXTURE_2D, palette_data->texture);

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
    */

    return palette_data;
}

void free_palette_data(Palette_Data* palette_data)
{
    if (palette_data == NULL) {
        return;
    }

    if (palette_data->buffer != NULL) {
        free(palette_data->buffer);
    }

    free(palette_data);
}