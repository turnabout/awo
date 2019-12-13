#include <stdlib.h>

#include "Game/Data/Palette/game_palette.h"
#include "Game/Entity/Tile/Property_Tile/property_tile.h"
#include "Game/Entity/Tile/Property_Tile/_update_property_tile_grid.h"
#include "Game/Entity/Tile/Property_Tile/_update_property_tile_fog.h"
#include "Game/Renderer/game_renderer.h"

void delete_property_tile(void* property, Game_Clock* game_clock, Tiles_Data* tiles_data);

// Update which palette is used by the property in its render grid spot.
// Note: overwrites the fog palette if it was used.
void update_property_render_grid_palette(Property_Tile* property)
{
    GLfloat palette_index = get_player_property_palette_index((property->player->index));

    update_tile_layer_pixel_high( 
        TILE_LAYER_0, 
        property->x, 
        property->y, 
        (vec2) { palette_index, 0.0f } 
    );

    update_tile_layer_pixel_high( 
        TILE_LAYER_1, 
        property->x, 
        property->y, 
        (vec2) { palette_index, 0.0f } 
    );
}

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

    update_property_owner(tiles_data, property, player);

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

    update_property_render_grid_palette(property);
    property->update_render_grid(property, 0);

    return property;
}

void update_property_owner(Tiles_Data* tiles_data, Property_Tile* property, Player* player)
{
    property->player = player;

    property->frame = get_property_type_frame(
        tiles_data,
        (Property_Type)property->type - PROPERTY_TILE_TYPE_FIRST,
        property->player->CO->army
    );

    update_property_render_grid_palette(property);
}

void delete_property_tile(void* property_arg , Game_Clock* game_clock, Tiles_Data* tiles_data)
{
    if (property_arg == NULL) {
        return;
    }

    Property_Tile* property = (Property_Tile*)property_arg;

    if (property->type == Property_Base) {
        unregister_game_clock_tile(
            game_clock, 
            (Tile*)property, 
            Base_Smoke_Clock, 
            Base_Smoke_Sub_Clock
        );
    }

    clear_tile_layers_pixel(property->x, property->y);
    free(property);
}