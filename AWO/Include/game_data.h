#pragma once

#include "game.h"

/*! @brief Gets the next neutral tile type.
 *
 *  @note Must be called continuously until it returns NULL.
 *
 *  @param[out] type Filled in with the neutral tile type's value.
 *  @return The tile type's string.
 */
const char* get_next_game_tile_type_data(int* type);

/*! @brief Gets the next neutral tile variation for a type.
 *
 *  @note Must be called continuously until it returns NULL.
 *
 *  @param[in] game The game instance.
 *  @param[in] type The type from which to get the next variation.
 *  @param[out] var Filled in with the neutral tile variation's value.
 *  @return The tile variation's string.
 */
const char* get_next_game_tile_var_data(Game* game, int type, char* var);