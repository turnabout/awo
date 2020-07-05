#pragma once

#include "AWO/types.h"
#include "Game/Renderer/game_renderer.h"
#include "Game/Clock/game_clock.h"
#include "Game/Data/Tile/tiles_data.h"

/*! @brief Callback function stored on and used by entities to update their render grid pixel.
 *
 *  @param[in] renderer Reference to the game renderer.
 *  @param[in] entity The entity to update.
 *  @param[in] animation_index The animation index of the frame used to update the render grid.
 *  @param[in] data Data on how to update. Implementation-defined.
 */
typedef void (*update_entity_render_grid_cb)(Game_Renderer* renderer, void* entity, Uint8 data);

/*! @brief Callback function stored on and used by entities to update their palette.
 *
 *  @param[in] renderer Reference to the game renderer.
 *  @param[in] entity The entity to update.
 *  @param[in] data Data on which palette to update to. Implementation-defined.
 */
typedef void (*update_entity_palette_cb)(Game_Renderer* renderer, void* entity, Uint8 data);

/*! @brief Callback function stored on and used by entities to delete themselves.
 *
 *  @param[in] renderer Reference to the game renderer.
 *  @param[in] entity The entity to delete.
 *  @param[in] game_clock Reference to the game clock module.
 *  @param[in] data_module Reference to a data module. Implementation-defined.
 */
typedef void (*delete_entity_cb)(
    Game_Renderer* renderer, 
    Game_Clock* game_clock, 
    void* entity, 
    void* data_module
);
