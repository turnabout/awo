#include <stdlib.h>

#include "Game/Entity/Tile/Property_Tile/property_tile.h"

Property_Tile* create_property_tile(
    Game_Clock* game_clock,
    Tiles_Data* tiles_data,
    Tile_Type tile_type,
    Player_Index player,
    tile_update_render_grid_cb* update_render_grid_cb
)
{
    Property_Tile* property_tile = (Property_Tile*)malloc(sizeof(Property_Tile));

    property_tile->type = tile_type;
    property_tile->player = player;

    // TODO
    // property_tile->frame = get_property_frame(tiles_data, property_type, Clear, player);

    // TODO: set update_render_grid_cb

    return property_tile;
}