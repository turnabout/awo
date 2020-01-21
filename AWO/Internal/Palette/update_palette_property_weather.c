#include <stdlib.h>

#include "Palette/_palette.h"

void apply_property_palettes_weather_color(
    Palette_Data_Row* palette_texture_data, 
    Uint8 color_index,
    GLuint color[3]
)
{
    // Get index to first property palette row
    GLuint palette_index_row = get_player_property_palette_index_i(PLAYER_INDEX_FIRST);

    // Loop every property palette rows, apply color to each of them
    for (int i = 0; i < PLAYER_INDEX_COUNT; i++) {
        palette_texture_data[palette_index_row + i][color_index][0] = color[0];
        palette_texture_data[palette_index_row + i][color_index][1] = color[1];
        palette_texture_data[palette_index_row + i][color_index][2] = color[2];
        palette_texture_data[palette_index_row + i][color_index][3] = 255;
    }
}

void update_properties_weather_colors(GLuint game_palette_texture)
{
    // Load the game's palette texture data
    Palette_Data_Row* palette_buffer = malloc(
        sizeof(Palette_Data_Row) * PALETTE_TEX_HEIGHT
    );

    read_texture_data(
        game_palette_texture, 
        palette_buffer,
        PALETTE_TEX_WIDTH,
        PALETTE_TEX_HEIGHT
    );

    // Apply active tile palette colors to property palettes colors
    GLuint active_tile_palette_row = get_active_tile_palette_index_i(FALSE);
    GLuint active_fog_tile_palette_row = get_active_tile_palette_index_i(TRUE);
    GLuint fog_property_palette_row = get_fog_property_palette_index_i();

    for (int i = 0; i < PALETTE_TEX_WIDTH; i++) {

        // Apply this tile palette color  but only if it isn't an empty color 
        // (so we don't overwrite property palette's own colors)
        if (palette_buffer[active_tile_palette_row][i][3] != 0) {

            GLuint color[3] = {
                palette_buffer[active_tile_palette_row][i][0], 
                palette_buffer[active_tile_palette_row][i][1], 
                palette_buffer[active_tile_palette_row][i][2]
            };

            // Apply the color to all player property palettes
            apply_property_palettes_weather_color(palette_buffer, i, color);
        }

        // Apply the fog color to the fog property palette
        if (palette_buffer[active_fog_tile_palette_row][i][3] != 0) {

            GLuint color[3] = {
                palette_buffer[active_fog_tile_palette_row][i][0], 
                palette_buffer[active_fog_tile_palette_row][i][1], 
                palette_buffer[active_fog_tile_palette_row][i][2]
            };

            palette_buffer[fog_property_palette_row][i][0] = color[0];
            palette_buffer[fog_property_palette_row][i][1] = color[1];
            palette_buffer[fog_property_palette_row][i][2] = color[2];
            palette_buffer[fog_property_palette_row][i][3] = 255;
        }
    }

    // Save the new palette texture
    glTexSubImage2D(
        GL_TEXTURE_2D,
        0,
        0,
        0,
        PALETTE_TEX_WIDTH,
        PALETTE_TEX_HEIGHT,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        palette_buffer
    );

    free(palette_buffer);
}
