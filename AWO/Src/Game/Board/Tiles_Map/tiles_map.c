#include <stdlib.h>
#include <string.h>

#include "c_hashmap.h"
#include "Game/Entities/Tile/tile.h"
#include "tiles_map.h"

#define HASH_KEY_SIZE 3// 2 chars representing type & var, + 1 char for null-terminator

#pragma warning( disable : 6011 )

struct Tiles_Map {
    map_t map;
};

Tiles_Map* TM_create()
{
    Tiles_Map* tm = malloc(sizeof(Tiles_Map));

    tm->map = hashmap_new();
    return tm;
}

// Gets the hash key representing a tile in the tiles map
char* get_tile_hash_key(tile_type tt, tile_var tv)
{
    char* result = malloc(HASH_KEY_SIZE); 

    memcpy(result, tile_type_str_short[tt], 1);
    memcpy(result + 1, tile_var_str_short[tv], 2); // 2 to copy the null-terminator

    return result;
}

Tile* TM_get_map_tile(Tiles_Map* tm, tile_type tt, tile_var tv)
{
    Tile* tile;
    char* hash_key = get_tile_hash_key(tt, tv);

    if (hashmap_get(tm->map, hash_key, (void**)(&tile)) == MAP_MISSING) {
        free(hash_key);
        return NULL;
    }

    free(hash_key);
    return tile;
}

void TM_add_map_tile(Tiles_Map* tm, Tile* tile, tile_type tt, tile_var tv)
{
    char* hash_key = get_tile_hash_key(tt, tv);

    hashmap_put(tm->map, hash_key, tile);
    free(hash_key);
}