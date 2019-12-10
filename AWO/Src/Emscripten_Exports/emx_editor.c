#include "conf.h"
#include "Emscripten_Exports/emx.h"
#include "Game/_game.h"
#include "Game/Editor/editor.h"
#include "Game/Data/Tile/tiles_data.h"

// Gets the next basic tile type string. Must be called continuously until it returns NULL.
const char* EMX editor_get_next_tile_type()
{
    // Tile type index
    static int type_index = NEUTRAL_TILE_TYPE_BASIC_FIRST;

    // No more tile types to loop, reset index and return NULL to stop looping
    if (type_index == NEUTRAL_TILE_TYPE_BASIC_LAST) {
        type_index = NEUTRAL_TILE_TYPE_BASIC_FIRST;
        return NULL;
    }

    return tile_type_str[type_index++];
}

// Gets the next tile variation data of the given tile type.
// Stores variation value in given pointer & returns variation string.
const char* EMX editor_get_next_tile_var(Game* game, Tile_Type tile_type, Uint8* var_val)
{
    // return TD_get_next_tile_var_data(game->td, tile_type, var_val);
    return ""; // TODO
}

// Updates the editor's tile type with the given one.
void EMX editor_update_tile_type(Game* game, Tile_Type type)
{
    update_editor_selected_tile_type(game->editor, type, TILE_VAR_NONE);
}
