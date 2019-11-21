#include <stdlib.h>

#include "Game/Entity/Tile/Property_Tile/property_tile.h"

Property_Tile* create_property_tile(
    Game_Clock* game_clock,
    Tiles_Data* tiles_data,
    Tile_Type tile_type,
    Army_Type color_army,
    Uint8 x,
    Uint8 y
)
{
    Property_Tile* tile = (Property_Tile*)malloc(sizeof(Property_Tile));

    tile->type = tile_type;
    tile->color_army = color_army;
    tile->visual_army = ARMY_TYPE_FIRST;
    tile->x = x;
    tile->y = y;

    // TODO
    // property_tile->frame = get_property_frame(tiles_data, property_type, Clear, player);

    // TODO: set update_render_grid_cb

    return tile;
}

void update_property_army(Property_Tile* property, Army_Type color_army, Army_Type visual_army)
{
    property->color_army = color_army;
    property->visual_army = visual_army;

    // TODO: update palette
}