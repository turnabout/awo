#include <stdlib.h>

#include "emx.h"
#include "Game/_game.h"
#include "GL_Helpers/Texture_Reader/texture_reader.h"

unsigned char* EMX test_entity_visuals_reader(Game* game, int* width_out, int* height_out)
{
    Texture_Reader* reader = create_texture_reader(
        game->data->sprite_sheet,
        game->data->sprite_sheet_width,
        game->data->sprite_sheet_height
    );

    int width = 16;
    int height = 16;
    int x = 0;
    int y = 0;
    unsigned char* buf = read_texture_src_data(reader, x, y, width, height);

    free_texture_reader(reader);

    *width_out = width;
    *height_out = height;

    return buf;

    /*
    int width = 20;
    int height = 20;
    int len = (width * height) * 4;
    unsigned char* out = malloc(sizeof(char) * len);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            out[((x * 4) + (y * width * 4)) + 0] = 50;
            out[((x * 4) + (y * width * 4)) + 1] = 0;
            out[((x * 4) + (y * width * 4)) + 2] = 0;
            out[((x * 4) + (y * width * 4)) + 3] = 255;
        }

    }

    for (int i = 0; i < len; i++) {
        // printf("out[%d] = %d\n", i, out[i]);
    }

    out[0] = 0;
    out[1] = 255;
    out[2] = 0;
    out[3] = 255;

    *width_out = width;
    *height_out = height;
    return out;
    */
}