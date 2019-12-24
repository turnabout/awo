#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "GL_Helpers/gl_helpers.h"
#include "GL_Helpers/Texture_Reader/texture_reader.h"

struct Texture_Reader {

    // Dimensions of the texture this reader reads from.
    int texture_w, texture_h;

    // Buffer containing the data for the texture.
    Uint8* texture_buffer;

};

Texture_Reader* create_texture_reader(GLuint texture, int texture_w, int texture_h)
{
    Texture_Reader* reader = malloc(sizeof(Texture_Reader));

    reader->texture_buffer = malloc(sizeof(Uint8) * 4 * texture_w * texture_h);
    reader->texture_w = texture_w;
    reader->texture_h = texture_h;

    read_texture_data(texture, reader->texture_buffer, texture_w, texture_h);

    return reader;
}

Uint8* read_texture_src_data(Texture_Reader* reader, int x, int y, int w, int h)
{
    // Buffer containing texture data for the source we want
    Uint8* source_buffer = malloc((sizeof(Uint8) * 4) * w * h);

    // Ensure given section coordinates don't go outside the sprite sheet boundaries
    if ((x + w) >= reader->texture_w || (y + h) >= reader->texture_h) {
        // TODO: Error
        return NULL;
    }

    // Copy reader texture data to the section buffer
    for (int looped_y = y; looped_y < (y + h); looped_y++) {

        memcpy(
            (void*)&source_buffer[(y * w * 4)],
            (void*)&reader->texture_buffer[(x * 4) + (y * w * 4)],
            (w * 4)
        );
    }

    // Test
    /*
    for (int in_y = 0; in_y < w; in_y++) {
        for (int in_x = 0; in_x < h; in_x++) {
            printf(
                "[%d, %d]: [%d, %d, %d, %d]", 
                in_x, 
                in_y,
                source_buffer[((x * 4) + (y * w * 4)) + 0],
                source_buffer[((x * 4) + (y * w * 4)) + 1],
                source_buffer[((x * 4) + (y * w * 4)) + 2],
                source_buffer[((x * 4) + (y * w * 4)) + 3]
            );
        }
        printf("\n");
    }
    */

    return source_buffer;
}

void free_texture_reader(Texture_Reader* texture_reader)
{
    if (texture_reader != NULL) {

        if (texture_reader->texture_buffer != NULL) {
            free(texture_reader->texture_buffer);
        }

        free(texture_reader);
    }
}
