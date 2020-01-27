#include "Game/Entity/Tile/Property/_property_tile.h"

void delete_property_tile(
    Game_Renderer* game_renderer,
    Game_Clock* game_clock,
    void* property_arg,
    void* tiles_data
)
{
    if (property_arg == NULL) {
        return;
    }

    Property_Tile* property = (Property_Tile*)property_arg;

    if (property->type == Property_Base) {

        unregister_game_clock_tile(
            game_clock, 
            (Tile*)property, 
            Smoke_Clock
        );
    }

    clear_tile_layers_pixel(game_renderer, property->x, property->y);
    free(property);
}
