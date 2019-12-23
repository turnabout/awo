#include <stdlib.h>

#include "emx.h"
#include "Include/game_data.h"

unsigned char* EMX test_entity_visuals_reader(Game* game, int* len_out)
{
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

    *len_out = len;
    return out;
}