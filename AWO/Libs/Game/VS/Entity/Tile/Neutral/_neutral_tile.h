#pragma once

#include "Game/Entity/Tile/Neutral/neutral_tile.h"

/*! Tiles update callbacks.
 */

/*! @brief Updates a neutral tile's occupied render grid pixel.
 */
void update_tile_render_grid(Game_Renderer* renderer, void* tile, Uint8 animation_index);

/*! @brief Updates a neutral tile's occupied render grid pixel.
 *
 *  @note For 2-tiles tall tiles.
 */
void update_tall_tile_render_grid(Game_Renderer* renderer, void* tile, Uint8 animation_index);

/*! @brief Updates a neutral tile's palette.
 */
void update_tile_palette(Game_Renderer* renderer, void* tile, Bool fog);

/*! @brief Updates a neutral tile's palette.
 *
 *  @note For 2-tiles tall tiles.
 */
void update_tall_tile_palette(Game_Renderer* renderer, void* tile, Bool fog);

/*! @brief Deletes a property.
 */
void delete_neutral_tile(
    Game_Renderer* renderer, 
    Clock* game_clock,
    void* tile, 
    void* tiles_data
);
