#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <c_hashmap.h>

#include "Game/Entity/Tile/tile.h"
#include "Game/Entity/Tile/Hashmap/tiles_hashmap.h"

#define HASH_KEY_SIZE 3 // 2 chars representing type & variation, + 1 char for null-terminator

struct Tiles_Hashmap {
    map_t map;
};

typedef struct Tile_Map_Entry {
    char key_string[HASH_KEY_SIZE];

    Tile* tile;
} Tile_Map_Entry;

Tiles_Hashmap* create_tiles_hashmap()
{
    Tiles_Hashmap* tiles_hashmap = malloc(sizeof(Tiles_Hashmap));

    tiles_hashmap->map = hashmap_new();
    return tiles_hashmap;
}

Tile* get_hashmap_tile(Tiles_Hashmap* tiles_hashmap, Tile_Type type, Tile_Variation variation)
{
    Tile_Map_Entry* entry;
    char key_string[HASH_KEY_SIZE];

    snprintf(
        key_string, 
        HASH_KEY_SIZE,
        "%s%s",
        tile_type_str_short[type],
        tile_var_str_short[variation]
    );
    
    if (hashmap_get(tiles_hashmap->map, key_string, (void**)(&entry)) == MAP_MISSING) {
        return NULL;
    }

    return entry->tile;
}

void add_hashmap_tile(
    Tiles_Hashmap* tiles_hashmap, 
    Tile* tile, 
    Tile_Type type, 
    Tile_Variation variation
)
{
    // Create hashmap entry with key string & tile, then add to hashmap
    Tile_Map_Entry* entry = malloc(sizeof(Tile_Map_Entry));

    snprintf(
        entry->key_string, 
        HASH_KEY_SIZE, 
        "%s%s", 
        tile_type_str_short[type], 
        tile_var_str_short[variation]
    );

    entry->tile = tile;

    hashmap_put(tiles_hashmap->map, entry->key_string, entry);
}

// Callback used to iterate over every hashmap entry & free their contents.
int free_tiles_hashmap_entry_CB(any_t tiles_hashmap_arg, any_t entry_arg)
{
    Tile_Map_Entry* entry = (Tile_Map_Entry*)entry_arg;
    Tiles_Hashmap* tiles_hashmap = (Tiles_Hashmap*)tiles_hashmap_arg;

    // Remove entry from hashmap
    hashmap_remove(tiles_hashmap->map, entry->key_string);

    // Free memory from entry and its tile
    free_tile(entry->tile);
    free(entry);

    return MAP_OK;
}

void free_tiles_hashmap(Tiles_Hashmap* tiles_hashmap)
{
    if (tiles_hashmap != NULL) {
        hashmap_iterate(tiles_hashmap->map, free_tiles_hashmap_entry_CB, tiles_hashmap);

        hashmap_free(tiles_hashmap->map);
        free(tiles_hashmap);
    }
}