#include <stdlib.h>

#include "Game/Entity/Tile/Factory/tile_factory.h"
#include "Game/Entity/Tile/Hashmap/tiles_hashmap.h"

struct Tile_Factory {

    // Map holding every unique tile.
    Tiles_Hashmap* map;

    // Reference to the game's tiles' data.
    Tiles_Data* tiles_data;

    // Reference to the game clock.
    Game_Clock* game_clock;
};

Tile_Factory* TF_create(Tiles_Data* tiles_data, Game_Clock* game_clock)
{
    Tile_Factory* factory = malloc(sizeof(Tile_Factory));

    factory->tiles_data = tiles_data;
    factory->game_clock = game_clock;
    factory->map = create_tiles_hashmap();

    return factory;
}

Tile* TF_get_tile(Tile_Factory* factory, Tile_Type type, Tile_Variation variation)
{
    // Attempt to get existing tile from map
    Tile* tile = get_hashmap_tile(factory->map, type, variation);

    // If nonexistent, make new one and add to map
    if (tile == NULL) {
        tile = create_tile(factory->game_clock, factory->tiles_data, type, variation);
        add_hashmap_tile(factory->map, tile, type, variation);
    }

    return tile;
}