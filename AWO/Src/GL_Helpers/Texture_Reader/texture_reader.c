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

    // Size of a line in the loaded texture
    int texture_line_size;

};

Texture_Reader* create_texture_reader(GLuint texture, int texture_w, int texture_h)
{
    Texture_Reader* reader = malloc(sizeof(Texture_Reader));

    reader->texture_buffer = malloc(sizeof(Uint8) * 4 * texture_w * texture_h);
    reader->texture_w = texture_w;
    reader->texture_h = texture_h;
    reader->texture_line_size = texture_w * 4;

    read_texture_data(texture, reader->texture_buffer, texture_w, texture_h);

    return reader;
}

Uint8* read_texture_src_data(Texture_Reader* reader, int src_x, int src_y, int src_w, int src_h)
{
    // Buffer containing texture data for the desired source
    Uint8* out_buffer = malloc((sizeof(Uint8) * 4) * src_w * src_h);

    // Ensure given section coordinates don't go outside the sprite sheet boundaries
    if ((src_x + src_w) >= reader->texture_w || (src_y + src_h) >= reader->texture_h) {
        // TODO: Error
        return NULL;
    }

    // Size of a copied line in bytes
    int line_size = (src_w * 4);

    // Copy texture data to the source buffer, line by line
    for (int y = 0; y < src_w; y++) {

        // Gets the location to copy from the texture
        // First line: Y location 
        // Second line: X location
        int texture_buffer_location = (
            ((src_y + y) * reader->texture_line_size) + 
            (src_x * 4)
        );

        memcpy(
            (void*)&out_buffer[(y * line_size)],
            (void*)&reader->texture_buffer[texture_buffer_location],
            line_size
        );
    }

    return out_buffer;
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
