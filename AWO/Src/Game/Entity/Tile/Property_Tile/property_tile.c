#include <stdlib.h>

#include "Game/Entity/Tile/Property_Tile/property_tile.h"
#include "Game/Entity/Tile/Property_Tile/_update_property_tile_animation.h"
#include "Game/Entity/Tile/Property_Tile/_update_property_tile_fog.h"

Property_Tile* create_property_tile(
    Game_Clock* game_clock,
    Tiles_Data* tiles_data,
    Tile_Type tile_type,
    Army_Type color_army,
    Uint8 x,
    Uint8 y
)
{
    Property_Tile* property = (Property_Tile*)malloc(sizeof(Property_Tile));

    property->type = tile_type;
    property->color_army = color_army;
    property->visual_army = ARMY_TYPE_FIRST;
    property->x = x;
    property->y = y;

    property->data = get_property_type_data(
        tiles_data,
        (Property_Type)tile_type - PROPERTY_TILE_TYPE_FIRST
    );

    // TODO: set weather from somewhere
    property->frame = get_property_type_frame(property->data, Clear, property->visual_army);

    // TODO: base properties contain an animation which makes them update differently
    if (tile_type == Property_Base) {
    } else {
    }

    // Set update callbacks
    property->update_render_grid = update_regular_property_render_grid;
    property->update_fog = update_regular_property_fog_status;


    return property;
}

void update_property_army(Property_Tile* property, Army_Type color_army, Army_Type visual_army)
{
    property->color_army = color_army;
    property->visual_army = visual_army;

    property->frame = get_property_type_frame(property->data, Clear, property->visual_army);

    // TODO: update palette
}