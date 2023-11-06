#include <stdlib.h>

#include "Game/Entity/Tile/Property/_property_tile.h"

Property_Tile* create_property_tile(
    Clock* game_clock,
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

    update_property_owner(property, tiles_data, player);

    if (tile_type == Property_Base) {

        // Register game clock to update the base smoke animation
        register_game_clock_tile(game_clock, (Tile*)property, Smoke_Clock);
        gather_tile_data(tiles_data, Base_Smoke, Default, NULL, &property->base_smoke);

        property->update_grid = update_base_render_grid;
        property->update_palette = update_base_palette;
    } else {
        property->update_grid = update_property_render_grid;
        property->update_palette = update_property_palette;
    }

    return property;
}

void update_property_owner(Property_Tile* property, Tiles_Data* tiles_data, Player* player)
{
    property->player = player;

    property->frame = get_property_type_frame(
        tiles_data,
        (Property_Type)property->type - PROPERTY_TILE_TYPE_FIRST,
        property->player->CO->army
    );
}
