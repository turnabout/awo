#pragma once

#include "Game/Entity/Tile/Property_Tile/property_tile.h"

/*! Properties update callbacks.
 */

/*! @brief Updates a property's occupied render grid pixel.
 */
void update_property_render_grid(Game_Renderer* renderer, void* tile, Uint8 animation_index);

/*! @brief Updates a property's occupied render grid pixel.
 *
 *  @note For base tiles.
 */
void update_base_render_grid(Game_Renderer* renderer, void* tile, Uint8 animation_index);

/*! @brief Updates a property's palette.
 */
void update_property_palette(Game_Renderer* renderer, void* tile, Bool fog);

/*! @brief Updates a property's palette.
 *
 *  @note For base tiles.
 */
void update_base_palette(Game_Renderer* renderer, void* tile, Bool fog);

/*! @brief Deletes a property.
 */
void delete_property_tile(
    Game_Renderer* game_renderer,
    Game_Clock* game_clock,
    void* property,
    void* tiles_data
);