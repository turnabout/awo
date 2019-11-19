#include <stdlib.h>

#include "Game/Entity/Tile/Property_Tile/property_tile.h"

Property_Tile* create_property_tile(
    Tile* parent_tile,
    Game_Clock* game_clock,
    Tiles_Data* tiles_data,
    Property_Type property_type,
    Player_Index player,
    tile_update_render_grid_cb* update_render_grid_cb
)
{
    Property_Tile* property_tile = (Property_Tile*)malloc(sizeof(Property_Tile));

    property_tile->type = property_type;
    property_tile->player = player;

    property_tile->frame = get_property_frame(tiles_data, property_type, Clear, player);

    return property_tile;
}