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

void register_tile_position(Tile* tile, Uint8 x, Uint8 y);
void update_tile_animation_index(Tile* tile, Uint8 index);

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
