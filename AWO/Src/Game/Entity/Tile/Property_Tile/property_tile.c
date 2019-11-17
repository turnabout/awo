#include <stdlib.h>

#include "Game/Entity/Tile/Property_Tile/property_tile.h"

Property_Tile* create_property_tile(
    Game_Clock* game_clock,
    Tiles_Data* tiles_data,
    Property_Type property_type,
    Weather weather,
    Unit_Variation army,
    tile_update_render_grid_cb* update_render_grid_cb
)
{
    Property_Tile* property_tile = (Property_Tile*)malloc(sizeof(Property_Tile));

    property_tile->type = property_type;
    property_tile->army = army;

    property_tile->frame = get_property_frame(tiles_data, property_type, weather, army);

    return property_tile;
}