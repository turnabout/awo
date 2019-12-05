#include <stdlib.h>

#include "Game/Entity/Tile/Property_Tile/property_tile.h"
#include "Game/Entity/Tile/Property_Tile/_update_property_tile_grid.h"
#include "Game/Entity/Tile/Property_Tile/_update_property_tile_fog.h"

void delete_property_tile(Neutral_Tile* property, Game_Clock* game_clock, Tiles_Data* tiles_data);

Property_Tile* create_property_tile(
    Game_Clock* game_clock,
    Tiles_Data* tiles_data,
    Tile_Type tile_type,
    Player* player,
    Uint8 x,
    Uint8 y
)
{
    Property_Tile* property = malloc(sizeof(Property_Tile));

    property->type = tile_type;
    property->x = x;
    property->y = y;
    property->delete = delete_property_tile;

    property->data = get_property_type_data(
        tiles_data,
        WEATHER_FIRST,
        (Property_Type)tile_type - PROPERTY_TILE_TYPE_FIRST
    );

    update_property_owner(property, player);

    if (tile_type == Property_Base) {

        // Register game clock to update the base smoke animation
        register_game_clock_tile(game_clock, (Tile*)property, Base_Smoke_Clock, Base_Smoke_Sub_Clock);

        gather_tile_data(tiles_data, Base_Smoke, Default, NULL, NULL, &property->base_smoke);

        property->update_render_grid = update_base_render_grid;
        property->update_fog = update_base_fog_status;
    } else {
        property->update_render_grid = update_regular_property_render_grid;
        property->update_fog = update_regular_property_fog_status;
    }

    property->update_fog(property, FALSE);
    property->update_render_grid(property, 0);

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

void delete_property_tile(Neutral_Tile* property, Game_Clock* game_clock, Tiles_Data* tiles_data)
{
    if (property == NULL) {
        return;
    }

    if (property->type == Property_Base) {
        unregister_game_clock_tile(game_clock, (Tile*)property, Base_Smoke_Clock, Base_Smoke_Sub_Clock);
    }

    free(property);
}