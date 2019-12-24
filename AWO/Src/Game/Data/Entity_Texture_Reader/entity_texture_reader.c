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

    read_texture_data(
        game_raw_palette,
        (void*)reader->palette_data,
        PALETTE_TEX_WIDTH,
        PALETTE_TEX_HEIGHT
    );

    return reader;
}

Uint8* read_neutral_tile_texture(
    Entity_Texture_Reader* reader, 
    Tile_Type type, 
    Tile_Variation variation,
    Weather weather
)
{
    // TODO
    return NULL;
}

void free_entity_texture_reader(Entity_Texture_Reader* reader)
{
    if (reader == NULL) {
        return;
    }

    free_texture_reader(reader->texture_reader);

    free(reader);
}