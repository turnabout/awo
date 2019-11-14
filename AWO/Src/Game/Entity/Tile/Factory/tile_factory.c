#include <stdlib.h>

#include "Game/Entity/Tile/Factory/tile_factory.h"
#include "Game/Entity/Tile/Hashmap/tiles_hashmap.h"

struct Tile_Factory {

    // Map holding every unique tile.
    Tiles_Hashmap* hashmap;

    // Reference to the game's tiles' data.
    Tiles_Data* tiles_data;

    // Reference to the game clock.
    Game_Clock* game_clock;

    // Module subscribing animated tiles to the game clock.
    Clock_Subscriber* tiles_clock_sub;
};

Tile_Factory* create_tile_factory(
    Tiles_Data* tiles_data, 
    Game_Clock* game_clock,
    Clock_Subscriber* tiles_clock_sub
)
{
    Tile_Factory* factory = malloc(sizeof(Tile_Factory));

    factory->tiles_data = tiles_data;
    factory->game_clock = game_clock;
    factory->hashmap = create_tiles_hashmap();
    factory->tiles_clock_sub = tiles_clock_sub;

    return factory;
}

Tile* get_tile_factory_tile(Tile_Factory* factory, Tile_Type type, Tile_Variation variation)
{
    // Attempt to get existing tile from hashmap
    Tile* tile = get_hashmap_tile(factory->hashmap, type, variation);

    // If nonexistent, make new one and add to hashmap
    if (tile == NULL) {
        tile = create_tile(factory->game_clock, factory->tiles_data, type, variation);
        add_hashmap_tile(factory->hashmap, tile, type, variation);

        // Register the new tile with the tiles clock subscriber module
        register_clock_subscriber_tile(factory->tiles_clock_sub, tile);
    }

    return tile;
}

void free_tile_factory(Tile_Factory* factory)
{
    if (factory != NULL) {
        free_tiles_hashmap(factory->hashmap);
        free(factory);
    }
}