#include <stdlib.h>

#include "conf.h"
#include "types.h"
#include "Game/_game.h"
#include "Game/Editor/game_editor.h"
#include "Game/Data/Tile/tiles_data.h"
#include "Emscripten_Exports/emx.h"

// Gets the next basic tile type string. Must be called continuously until it returns NULL.
const char* EMX editor_get_next_tile_type()
{
    Tile_Type type = get_next_basic_tile_type();

    if (type == TILE_TYPE_NONE) {
        return NULL;
    }

    return tile_type_str[type];
}

// Gets the next tile variation data of the given tile type.
// Stores variation value in given pointer & returns variation string.
const char* EMX editor_get_next_tile_var(Game* game, Tile_Type type, Uint8* var_val)
{
    Tile_Variation variation = get_next_tile_variation(game->tiles_data, type);

    *var_val = variation;

    if (variation == TILE_VAR_NONE) {
        return NULL;
    }

    return tile_var_str[variation];
}

// Updates the editor's tile type with the given one.
void EMX editor_update_selected_tile(
    Game* game, 
    Game_Editor_Entity_Kind kind, 
    int type, 
    int variation
)
{
    update_editor_selected_entity(game->editor, kind, type, variation);
}

Uint8* EMX testy(Game* game, int* len_out)
{
    int width = 20;
    int height = 20;
    int len = (width * height) * 4;
    Uint8* out = malloc(sizeof(Uint8) * len);

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
