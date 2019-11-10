#pragma once

#include <cglm/types.h>

#include "Game/Clock/game_clock.h"
#include "Game/Data/Tile/tiles_data.h"

/*! @brief Represents a game tile.
 */
typedef struct Tile Tile;

/*! @brief Creates a tile.
 *
 *  @param[in] game_clock The game clock.
 *  @param[in] tiles_data The tiles data object.
 *  @param[in] tile_type The type of the created tile.
 *  @param[in] tile_variation The variation of the created tile.
 *  @return The created tile.
 */
Tile* create_tile(
    Game_Clock* game_clock, 
    Tiles_Data* tiles_data, 
    Tile_Type type, 
    Tile_Variation variation
);

/*! @brief Draws a tile.
 *
 *  @param[in] tile The tile to draw.
 *  @param[in] sprite_batch The sprite batch object used to draw game sprites.
 *  @param[in] palette_index Index of the palette to draw the tile with.
 *  @param[in] destination Vector of screen coordinates to draw the tile at.
 */
// void draw_tile(Tile* tile, Sprite_Batch* sprite_batch, GLfloat palette_index, vec2 destination);

// Gets the tile type of the given tile.
/*! @brief Gets the tile type of the given tile.
 *  @param[in] The tile.
 *  @return The tile type.
 */
Tile_Type get_tile_type(Tile* tile);

/*! @brief Frees memory occupied by a tile.
 *  @param[in] The tile to free.
 */
void free_tile(Tile* tile);
