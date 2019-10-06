#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "c_hashmap.h"
#include "Game/Entities/Tile/tile.h"
#include "tiles_map.h"

#define HASH_KEY_SIZE 3 // 2 chars representing type & var, + 1 char for null-terminator

struct Tiles_Map {
    map_t map;
};

typedef struct Tile_Map_Entry {
    char key_string[HASH_KEY_SIZE];
    Tile* tile;
} Tile_Map_Entry;

Tiles_Map* TM_create()
{
    Tiles_Map* tm = malloc(sizeof(Tiles_Map));

    tm->map = hashmap_new();
    return tm;
}

Tile* TM_get_map_tile(Tiles_Map* tm, Tile_Type type, Tile_Var var)
{
    Tile_Map_Entry* entry;
    char key_string[HASH_KEY_SIZE];

    snprintf(key_string, HASH_KEY_SIZE, "%s%s", tile_type_str_short[type], tile_var_str_short[var]);
    
    if (hashmap_get(tm->map, key_string, (void**)(&entry)) == MAP_MISSING) {
        return NULL;
    }

    return entry->tile;
}

void TM_add_map_tile(Tiles_Map* tm, Tile* tile, Tile_Type type, Tile_Var var)
{
    // Create map entry with key string & tile, then add to map
    Tile_Map_Entry* entry = malloc(sizeof(Tile_Map_Entry));

    snprintf(entry->key_string, HASH_KEY_SIZE, "%s%s", tile_type_str_short[type], tile_var_str_short[var]);
    entry->tile = tile;

    hashmap_put(tm->map, entry->key_string, entry);
}