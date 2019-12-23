#include "emx.h"
#include "Game/_game.h"

const char* EMX get_next_game_tile_type(int* type_out)
{
    Tile_Type type = get_next_basic_tile_type();

    if (type == TILE_TYPE_NONE) {
        return NULL;
    }

    *type_out = type;
    return tile_type_str[type];
}

const char* EMX get_next_game_tile_variation(Game* game, int type, char* var_out)
{
    Tile_Variation variation = get_next_tile_variation(game->data->tiles, type);

    *var_out = variation;

    if (variation == TILE_VAR_NONE) {
        return NULL;
    }

    return tile_var_str[variation];
}