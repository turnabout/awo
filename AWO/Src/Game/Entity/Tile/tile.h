#pragma once

#include <cglm/types.h>

#include "Game/Clock/game_clock.h"
#include "Game/Data/Tile/tiles_data.h"
#include "Game/Renderer/game_renderer.h"

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

/*! @brief Renders a tile.
 *
 *  @param[in] tile The tile to draw.
 *  @param[in] renderer The game renderer.
 *  @param[in] x The x offset of the tile, in tiles.
 *  @param[in] y The y offset of the tile, in tiles.
 *  @param[in] palette_index Index of the palette used to render the tile.
 */
void render_tile(Tile* tile, Game_Renderer* renderer, int x, int y, GLfloat palette_index);

/*! @brief Gets the tile type of the given tile.
 *
 *  @param[in] The tile.
 *  @return The tile type.
 */
Tile_Type get_tile_type(Tile* tile);

/*! @brief Gets the clock data of the given tile.
 *
 *  @param[in] The tile.
 *  @param[out] The clock index.
 *  @param[out] The sub-clock index.
 */
void get_tile_clock_data(
    Tile* tile,
    Animation_Clock_Index* clock_index,
    Animation_Sub_Clock_Index* sub_clock_index
);

/*! @brief Frees memory occupied by a tile.
 *
 *  @param[in] The tile to free.
 */
void free_tile(Tile* tile);
