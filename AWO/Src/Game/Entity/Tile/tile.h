#pragma once

#include <cglm/types.h>

#include "Game/Clock/game_clock.h"
#include "Game/Data/Tile/tiles_data.h"
#include "Game/Renderer/game_renderer.h"

/*! @brief Represents a tile used in the game's tile map system.
 */
typedef struct Tile {

    // This tile's animation.
    Animation* animation;

    // The coordinates of every instances of this tile present in the game.
    Point* positions;

    // This tile's type.
    Tile_Type type;

    // This tile's variation.
    Tile_Variation variation;

    // How many instances of this tile exist in the game.
    Uint16 count;

    // Current animation index of tiles of this type/variation.
    Uint8 animation_index;
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

/*! @brief Updates the animation index currently used by the given tile.
 *
 *  @param[in] tile The tile.
 *  @param[in] index The new animation index to update to.
 */
void update_tile_animation_index(Tile* tile, Uint8 index);

/*! @brief Updates parts of the render grid occupied by the given tile.
 *
 *  @param[in] tile The tile.
 */
void update_tile_render_grid(Tile* tile);

/*! @brief Frees memory occupied by a tile.
 *
 *  @param[in] The tile to free.
 */
void free_tile(Tile* tile);
