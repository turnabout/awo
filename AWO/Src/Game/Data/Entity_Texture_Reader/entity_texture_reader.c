#include <string.h>
#include <stdlib.h>

#include "GL_Helpers/gl_helpers.h"
#include "GL_Helpers/Texture_Reader/texture_reader.h"
#include "Game/Data/Palette/raw_palette.h"
#include "Game/Data/Entity_Texture_Reader/entity_texture_reader.h"

struct Entity_Texture_Reader {

    // Reference to the game's tiles data module.
    Tiles_Data* tiles_data;

    // Reference to the game's units data module.
    Units_Data* units_data;

    // Buffer containing the data from the raw game palette.
    Uint8* palette_data;

    // The texture reader used to retrieve the texture for single entities.
    Texture_Reader* texture_reader;

};

Entity_Texture_Reader* create_entity_texture_reader(
    Tiles_Data* tiles_data,
    Units_Data* units_data,
    GLuint game_raw_palette,
    GLuint sprite_sheet,
    int sprite_sheet_w,
    int sprite_sheet_h
)
{
    Entity_Texture_Reader* reader = malloc(sizeof(Entity_Texture_Reader));

    reader->tiles_data = tiles_data;
    reader->units_data = units_data;

    reader->texture_reader = create_texture_reader(sprite_sheet, sprite_sheet_w, sprite_sheet_h);

    reader->palette_data = malloc(PALETTE_TEX_WIDTH * PALETTE_TEX_HEIGHT * 4);

    read_texture_data(
        game_raw_palette,
        (void*)reader->palette_data,
        PALETTE_TEX_WIDTH,
        PALETTE_TEX_HEIGHT
    );

    return reader;
}

// TODO: apply multiple palettes instead of just one
void apply_entity_texture_reader_palette(
    Entity_Texture_Reader* reader,
    Uint8* texture_buffer,
    int texture_w,
    int texture_h,
    GLuint applied_palette_row
)
{
    int line_size = texture_w * 4;
    int palette_line_loc = (applied_palette_row * PALETTE_TEX_WIDTH * 4);

    for (int y = 0; y < texture_h; y++) {

        for (int x = 0; x < texture_w; x++) {
            int looped_pixel_loc = (x * 4) + (y * line_size);

            // Don't bother with transparent pixels
            if (texture_buffer[looped_pixel_loc + 4] == 0) {
                continue;
            }

            // Get value of this pixel
            Uint8 red = texture_buffer[looped_pixel_loc + 0];

            // Use value to get location of palette pixel
            int palette_pixel_loc = (red * 4) + palette_line_loc;

            // Don't apply this palette pixel if its alpha is transparent
            if (reader->palette_data[palette_pixel_loc + 3] == 0) {
                continue;
            }

            // Apply palette color to the looped pixel
            memcpy(
                &texture_buffer[looped_pixel_loc],
                &reader->palette_data[palette_pixel_loc],
                4
            );

            /*
            printf(
                "[%d, %d] [%d, %d, %d, %d]\n", 
                y, 
                x, 
                reader->palette_data[palette_pixel_loc + 0],
                reader->palette_data[palette_pixel_loc + 1],
                reader->palette_data[palette_pixel_loc + 2],
                reader->palette_data[palette_pixel_loc + 3]
            );
            */
        }
    }
}

Uint8* read_neutral_tile_texture(
    Entity_Texture_Reader* reader, 
    Tile_Type type, 
    Tile_Variation variation,
    Weather weather,
    int* texture_w_out,
    int* texture_h_out
)
{
    Animation* tiles_anim;
    gather_tile_data(reader->tiles_data, type, variation, NULL, NULL, &tiles_anim);

    int texture_w = tiles_anim->frames[0].width;
    int texture_h = tiles_anim->frames[0].height;

    Uint8* texture_buffer = read_texture_src_data(
        reader->texture_reader,
        (int)tiles_anim->frames[0].raw_top_left[0],
        (int)tiles_anim->frames[0].raw_top_left[1],
        texture_w,
        texture_h
    );

    apply_entity_texture_reader_palette(
        reader, 
        texture_buffer, 
        texture_w, 
        texture_h,
        get_raw_tile_palette_index_i(weather, FALSE)
    );

    *texture_w_out = tiles_anim->frames[0].width;
    *texture_h_out = tiles_anim->frames[0].height;

    return texture_buffer;
}

void free_entity_texture_reader(Entity_Texture_Reader* reader)
{
    if (reader == NULL) {
        return;
    }

    if (reader->palette_data != NULL) {
        free(reader->palette_data);
    }

    free_texture_reader(reader->texture_reader);

    free(reader);
}