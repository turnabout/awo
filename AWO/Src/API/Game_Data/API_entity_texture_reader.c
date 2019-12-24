#include <stdlib.h>

#include "emx.h"
#include "Game/_game.h"
#include "GL_Helpers/Texture_Reader/texture_reader.h"
#include "Game/Data/Entity_Texture_Reader/entity_texture_reader.h"

Entity_Texture_Reader* EMX create_game_entity_visuals_reader(Game* game)
{
    return create_entity_texture_reader(
        game->data->tiles,
        game->data->units,
        game->data->raw_palette,
        game->data->sprite_sheet,
        game->data->sprite_sheet_width,
        game->data->sprite_sheet_height
    );
}

unsigned char* EMX read_game_entity_texture(
    Entity_Texture_Reader* reader,
    Entity_Kind kind,
    int type,
    int variation,
    int palette_variation,
    int* texture_width,
    int* texture_height
)
{
    if (kind == Entity_Kind_Neutral_Tile) {

        return read_neutral_tile_texture(
            reader,
            type,
            variation,
            palette_variation,
            texture_width,
            texture_height
        );

    } else if (kind == Entity_Kind_Property) {
        // TODO
        printf("Property texture reading not implemented\n");
        return NULL;
    } else if (kind == Entity_Kind_Unit) {
        // TODO
        printf("Unit texture reading not implemented\n");
        return NULL;
    } else {
        // TODO: error
        return NULL;
    }
}

void EMX free_game_entity_visuals_reader(Entity_Texture_Reader* reader)
{
    free_entity_texture_reader(reader);
}

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