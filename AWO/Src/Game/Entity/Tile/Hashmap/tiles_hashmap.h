#pragma once

#include "Game/Entity/Tile/tile.h"

// Used by game board. Holds a hashmap containing every unique tile contained within the game board.
typedef struct Tiles_Hashmap Tiles_Hashmap;

/*! @brief Creates a tiles hashmap.
 */
Tiles_Hashmap* create_tiles_hashmap();

/*! @brief Retrieves tile from the tiles hashmmap.
 *
 *  @param[in] tiles_map The tiles hashmap object to retrieve the tile from.
 *  @param[in] type The type of the tile to retrieve.
 *  @param[in] variation The variation of the tile to retrieve.
 *  @return The found tile or NULL if none was found.
 */
Tile* get_hashmap_tile(Tiles_Hashmap* tiles_map, Tile_Type type, Tile_Variation variation);

/*! @brief Adds a tile to the tiles hashmap.
 *
 *  @param[in] tiles_map The tiles hashmap object to add the tile to.
 *  @param[in] tile The tile to add.
 *  @param[in] type The type of the tile to add.
 *  @param[in] variation The variation of the tile to add.
 */
void add_hashmap_tile(
    Tiles_Hashmap* tiles_map, 
    Tile* tile, 
    Tile_Type type, 
    Tile_Variation variation
);

/*! @brief Frees a tile hashmap along with its stored tiles.
 *
 *  @param[in] tiles_map The tiles hashmap object to add the tile to.
 */
void free_tiles_hashmap(Tiles_Hashmap* tiles_map);