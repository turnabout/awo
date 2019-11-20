#include <stdlib.h>

#include "Game/Entity/Tile/Property_Tile/property_tile.h"

Property_Tile* create_property_tile(
    Game_Clock* game_clock,
    Tiles_Data* tiles_data,
    Tile_Type tile_type,
    Player_Index player,
    Uint8 x,
    Uint8 y
)
{
    Property_Tile* tile = (Property_Tile*)malloc(sizeof(Property_Tile));

    tile->type = tile_type;
    tile->player = player;
    tile->x = x;
    tile->y = y;

    // TODO
    // property_tile->frame = get_property_frame(tiles_data, property_type, Clear, player);

    // TODO: set update_render_grid_cb

    return tile;
}