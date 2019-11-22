#include <stdlib.h>

#include "Game/Entity/Tile/Property_Tile/property_tile.h"
#include "Game/Entity/Tile/Property_Tile/_update_property_tile_animation.h"
#include "Game/Entity/Tile/Property_Tile/_update_property_tile_fog.h"

Property_Tile* create_property_tile(
    Game_Clock* game_clock,
    Tiles_Data* tiles_data,
    Tile_Type tile_type,
    Player* player,
    Uint8 x,
    Uint8 y
)
{
    Property_Tile* property = (Property_Tile*)malloc(sizeof(Property_Tile));

    property->type = tile_type;
    property->x = x;
    property->y = y;

    property->data = get_property_type_data(
        tiles_data,
        WEATHER_FIRST,
        (Property_Type)tile_type - PROPERTY_TILE_TYPE_FIRST
    );

    update_property_owner(property, player);

    // TODO: base properties contain an animation which makes them update differently
    if (tile_type == Property_Base) {
    } else {
    }

    // Set update callbacks
    property->update_render_grid = update_regular_property_render_grid;
    property->update_fog = update_regular_property_fog_status;

    property->update_render_grid(property, 0);
    property->update_fog(property, 0);

    return property;
}

void update_property_owner(Property_Tile* property, Player* player)
{
    property->player = player;

    property->frame = get_property_type_frame(
        property->data,
        property->player->CO->army
    );
}

void update_property_weather_variation(
    Tiles_Data* tiles_data, 
    Property_Tile* property, 
    Weather weather
)
{
    property->data = get_property_type_data(
        tiles_data,
        weather,
        (Property_Type)property->type - PROPERTY_TILE_TYPE_FIRST
    );

    property->frame = get_property_type_frame(
        property->data,
        property->player->CO->army
    );
}