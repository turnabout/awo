#include <string.h>
#include <stdlib.h>

#include "GL_Helpers/gl_helpers.h"
#include "AWO/game_data.h"
#include "Texture_Reader/texture_reader.h"
#include "entity_texture_reader.h"

// Maximum amount of palettes that can be applied to an entity texture
#define MAX_APPLIED_PALETTE_COUNT 2

struct Entity_Texture_Reader {

    // Reference to the game data module.
    Game_Data* game_data;

    // The texture reader used to retrieve the texture for single entities.
    Texture_Reader* texture_reader;

    // Generated sprite sheet texture
    GLuint texture;

};

Entity_Texture_Reader* create_entity_texture_reader(Game_Data* game_data)
{
    Entity_Texture_Reader* reader = malloc(sizeof(Entity_Texture_Reader));

    if (reader == NULL) {
        return NULL;
    }

    reader->texture = get_sprite_sheet_GL_texture(game_data->sprite_sheet);

    int ss_width, ss_height;
    get_sprite_sheet_dimensions(game_data->sprite_sheet, &ss_width, &ss_height);

    reader->game_data = game_data;
    reader->texture_reader = NULL;

    reader->texture_reader = create_texture_reader(reader->texture, ss_width, ss_height);

    if (reader->texture_reader == NULL) {
        free_entity_texture_reader(reader);
        return NULL;
    }

    return reader;
}

// TODO: adjust to use new Palette_Data module
void apply_entity_texture_reader_palette(
    Entity_Texture_Reader* reader,
    Uint8* result_texture_buffer,
    int texture_w,
    int texture_h,
    GLuint applied_palette_rows[MAX_APPLIED_PALETTE_COUNT],
    int palette_count
)
{
    /*
    int line_size = texture_w * 4;

    // Store locations of the given palette lines
    int palette_line_locs[MAX_APPLIED_PALETTE_COUNT];

    for (int i = 0; i < palette_count; i++) {
        palette_line_locs[i] = (applied_palette_rows[i] * PALETTE_TEX_WIDTH * 4);
    }

    for (int y = 0; y < texture_h; y++) {

        for (int x = 0; x < texture_w; x++) {
            int looped_pixel_loc = (x * 4) + (y * line_size);

            // Don't bother with transparent pixels
            if (result_texture_buffer[looped_pixel_loc + 3] == 0) {
                continue;
            }

            // Get value of this pixel
            Uint8 red = result_texture_buffer[looped_pixel_loc + 0];

            // Apply given palettes to this pixel
            for (int i = 0; i < palette_count; i++) {

                // Use value to get location of palette pixel
                int palette_pixel_loc = (red * 4) + palette_line_locs[i];

                // Don't apply this palette pixel if its alpha is transparent
                if (reader->palette_data[palette_pixel_loc + 3] == 0) {
                    continue;
                }

                // Apply palette color to the looped pixel
                memcpy(
                    &result_texture_buffer[looped_pixel_loc],
                    &reader->palette_data[palette_pixel_loc],
                    4
                );
            }
        }
    }
    */
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
    Animation* animation;
    gather_tile_data(reader->game_data->tile, type, variation, NULL, &animation);

    int texture_w = animation->frames[0].width;
    int texture_h = animation->frames[0].height;

    Uint8* texture_buffer = read_texture_src_data(
        reader->texture_reader,
        (int)animation->frames[0].raw_top_left[0],
        (int)animation->frames[0].raw_top_left[1],
        texture_w,
        texture_h
    );

    /*
    apply_entity_texture_reader_palette(
        reader, 
        texture_buffer, 
        texture_w, 
        texture_h,
        (GLuint[MAX_APPLIED_PALETTE_COUNT]) { get_raw_tile_palette_index_i(weather, FALSE) },
        1
    );
    */

    *texture_w_out = animation->frames[0].width;
    *texture_h_out = animation->frames[0].height;

    return texture_buffer;
}

void free_entity_texture_reader(Entity_Texture_Reader* reader)
{
    if (reader == NULL) {
        return;
    }

    free_texture_reader(reader->texture_reader);

    free(reader);
}