#pragma once

#include <cglm/types.h>

#include "Game/Clock/game_clock.h"
#include "Game/Data/Tile/tiles_data.h"
#include "Game/Renderer/game_renderer.h"

/*! @brief Callback function used by tiles to update the render grid.
 *
 *  @param[in] tile The tile whose corresponding render grid(s) pixels should be updated.
 *  @param[in] animation_index The animation index of the frame used to update the render grid.
 */
typedef void (*tile_update_render_grid_cb)();

/*! @brief Represents a tile used in the game's tile map system.
 */
typedef struct Tile {

    // This tile's animation.
    Animation* animation;

    // The coordinates of every instances of this tile present in the game.
    Point* positions;

    // Callback function used to update this tile's corresponding render grid pixels.
    tile_update_render_grid_cb update_render_grid;

    // This tile's type.
    Tile_Type type;

    // This tile's variation.
    Tile_Variation variation;

    // How many instances of this tile exist in the game.
    Uint16 count;
} Tile;

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

/*! @brief Registers a board position on the given tile.
 *
 * Appends the given x/y coordinate to the tile's list of tile positions. This is used to update 
 * the contents of the tiles render grid, and keep them updated.
 *
 *  @param[in] tile The tile.
 *  @param[in] x The x coordinate to register.
 *  @param[in] y The y coordinate to register.
 */
void register_tile_board_position(Tile* tile, Uint8 x, Uint8 y);

/*! @brief Frees memory occupied by a tile.
 *
 *  @param[in] The tile to free.
 */
void free_tile(Tile* tile);
