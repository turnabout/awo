#include "conf.h"
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
