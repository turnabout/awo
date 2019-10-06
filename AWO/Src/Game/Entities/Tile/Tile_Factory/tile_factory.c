#include "tile_factory.h"

#include "Game/Entities/Tile/Tiles_Map/tiles_map.h"

struct Tile_Factory {
    Tiles_Map*  map; // Map holding every unique tile.
    Tiles_Data* td;  // Reference to the game's tiles' data.
    Game_Clock* gc;  // Reference to the game clock.
};

Tile_Factory* TF_create(Tiles_Data* td, Game_Clock* gc)
{
    Tile_Factory* factory = malloc(sizeof(Tile_Factory));

    factory->td = td;
    factory->gc = gc;
    factory->map = TM_create();

    return factory;
}

Tile* TF_get_tile(Tile_Factory* factory, Tile_Type type, Tile_Var var)
{
    // Attempt to get existing tile from map
    Tile* tile = TM_get_map_tile(factory->map, type, var);

    // If nonexistent, make new one and add to map
    if (tile == NULL) {
        tile = tile_create(factory->gc, factory->td, type, var);
        TM_add_map_tile(factory->map, tile, type, var);
    }

    return tile;
}