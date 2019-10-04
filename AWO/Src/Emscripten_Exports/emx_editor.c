#ifdef __EMSCRIPTEN__
#include <SDL.h>

#include "conf.h"
#include "Game/game.h"
#include "Visuals/visuals_data.h"


// Gets the next tile type string. Must be called continuously until it returns NULL.
const char* editor_get_next_tile_type()
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
const char* editor_get_next_tile_var(Game* game, Tile_Type tt, Uint8* var_val)
{
    return get_next_tile_variation_data(game->td, tt, var_val);
}

#endif
