#include <stdlib.h>

#include "Palette/_palette.h"

// TODO: take in a unit variation as an arg instead of a palette index
void update_unit_palette_black_pixel(GLuint palette_index, GLubyte new_color)
{
    GLubyte new_color_array[4] = { new_color, new_color, new_color, 255 };

    glTexSubImage2D(
        GL_TEXTURE_2D,
        0,
        0,
        palette_index,
        1,
        1,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        &new_color_array
    );
}

void update_active_tile_palette(Weather weather, GLuint game_palette_tex, GLuint raw_palette_tex)
{
    // TODO: update using new palette data module
    /*
    // Load the raw palette texture data
    Palette_Data_Row* raw_palettes_tex_data = malloc(
        sizeof(Palette_Data_Row) * PALETTE_TEX_HEIGHT
    );

    read_texture_data(
        raw_palette_tex, 
        raw_palettes_tex_data,
        PALETTE_TEX_WIDTH,
        PALETTE_TEX_HEIGHT
    );

    glBindTexture(GL_TEXTURE_2D, game_palette_tex);

    // Apply tile palette row
    glTexSubImage2D(
        GL_TEXTURE_2D,
        0,
        0,
        get_active_tile_palette_index_i(FALSE),
        PALETTE_TEX_WIDTH,
        1,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        &raw_palettes_tex_data[get_raw_tile_palette_index_i(weather, FALSE)]
    );

    // Apply fog tile palette row
    glTexSubImage2D(
        GL_TEXTURE_2D,
        0,
        0,
        get_active_tile_palette_index_i(TRUE),
        PALETTE_TEX_WIDTH,
        1,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        &raw_palettes_tex_data[get_raw_tile_palette_index_i(weather, TRUE)]
    );

    free(raw_palettes_tex_data);

    // Update properties' weather color with the new one
    update_properties_weather_colors(game_palette_tex);
    */
}