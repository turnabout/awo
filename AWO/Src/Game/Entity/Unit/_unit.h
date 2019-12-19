#pragma once

#include "Game/Entity/Unit/unit.h"

/*! @brief Updates a unit's occupied render grid pixel.
 *
 *  @note For 2-tiles tall tiles.
 */
void update_unit_render_grid(Game_Renderer* renderer, void* unit, Uint8 animation_index);

/*! @brief Updates a unit's palette.
 */
void update_unit_palette(Game_Renderer* renderer, void* unit, Bool done);

/*! @brief Deletes a unit.
 */
void delete_unit(
    Game_Renderer* game_renderer,
    Game_Clock* game_clock,
    void* unit,
    void* units_data
);
