#ifdef __EMSCRIPTEN__

#include <SDL.h>
#include "conf.h"
#include "Game/game.h"
#include "Visuals/visuals_data.h"
#include "Game/Editor/editor.h"
#include "emx.h"


// Gets the next tile type string. Must be called continuously until it returns NULL.
const char* EMX editor_get_next_tile_type()
{
    // Tile type index
    static int tt_index = 0;

    // No more tile types to loop, reset index and return NULL to stop looping
    if (tt_index == TILE_TYPE_BASIC_LAST) {
        tt_index = 0;
        return NULL;
    }

    return tile_type_str[tt_index++];
}

// Gets the next tile variation data of the given tile type.
// Stores variation value in given pointer & returns variation string.
const char* EMX editor_get_next_tile_var(Game* game, Tile_Type tile_type, Uint8* var_val)
{
    return TD_get_next_tile_var_data(game->td, tile_type, var_val);
}

// Updates the editor's tile type with the given one.
void EMX editor_update_tile_type(Game* game, Tile_Type type)
{
    update_editor_selected_tile_type(game->editor, type);
}
#endif
