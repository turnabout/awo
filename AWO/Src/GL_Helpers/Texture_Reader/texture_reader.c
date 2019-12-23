#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "GL_Helpers/gl_helpers.h"
#include "GL_Helpers/Texture_Reader/texture_reader.h"

struct Texture_Reader {

    // The texture this texture reader reads from.
    GLuint texture;

    // Dimensions of the texture this reader reads from.
    int texture_w, texture_h;

    // Buffer containing the data for the texture.
    Uint8* texture_buf;

};

Texture_Reader* create_texture_reader(GLuint texture, int texture_w, int texture_h)
{
    Texture_Reader* reader = malloc(sizeof(Texture_Reader));

    /*
    // TEST
    // Buffer containing sprite sheet texture data
    Uint8* ss_buffer = malloc(
        sizeof(Uint8) * 4 * game->data->sprite_sheet_width * game->data->sprite_sheet_height
    );

    read_texture_data(
        game->data->sprite_sheet, 
        ss_buffer, 
        game->data->sprite_sheet_width, 
        game->data->sprite_sheet_height
    );


    int x = 0;
    int y = 0;
    int w = 16;
    int h = 16;

    int ss_w = game->data->sprite_sheet_width;
    int ss_h = game->data->sprite_sheet_height;

    // TODO: Ensure given section coordinates don't go outside the sprite sheet boundaries

    // Buffer containing texture data for the section we want
    Uint8* section_buffer = malloc((sizeof(Uint8) * 4) * w * h);

    // Transfer sprite sheet texture in the section buffer
    for (int looped_y = y; looped_y < (y + h); looped_y++) {

        memcpy(
            (void*)&section_buffer[(y * w * 4)],
            (void*)&ss_buffer[(x * 4) + (y * w * 4)],
            (w * 4)
        );

            // (y * width * 4)
    }

    for (int in_y = 0; in_y < w; in_y++) {
        for (int in_x = 0; in_x < h; in_x++) {
            printf(
                "[%d, %d]: [%d, %d, %d, %d]", 
                in_x, 
                in_y,
                section_buffer[((x * 4) + (y * w * 4)) + 0],
                section_buffer[((x * 4) + (y * w * 4)) + 1],
                section_buffer[((x * 4) + (y * w * 4)) + 2],
                section_buffer[((x * 4) + (y * w * 4)) + 3]
            );
        }
        printf("\n");
    }
    */


        /*
        for (int looped_x = x; looped_x < (x + w); looped_x++) {

            // section_buffer[((x * 4) + (y * width * 4)) + 1]


            printf("{%d, %d}", looped_x, looped_y);
        }
        printf("\n");
        */

    return reader;
}

void read_texture_src_data(Texture_Reader* texture_reader, int x, int y, int w, int h)
{
}

void free_texture_reader(Texture_Reader* texture_reader)
{
    if (texture_reader != NULL) {

        if (texture_reader->texture_buf != NULL) {
            free(texture_reader->texture_buf);
        }

        free(texture_reader);
    }
}
