/**
 * Visuals processing for all types of entities.
 */

#pragma once
#include <SDL.h>
#include "../game.h"

/**
 *  \brief Creates and returns a texture for a units' army.
 *
 *  \param game Pointer to the game instance.
 *
 *  \return Returns ERR if an error occurred, or OK.
 *
 *  \sa create_units_texture()
 */
SDL_Texture* create_units_texture(Game* game);
