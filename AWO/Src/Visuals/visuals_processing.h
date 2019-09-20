#pragma once
#include <SDL.h>
#include "game.h"
#include "Data/Units/units_enums.h"

/**
 *  \brief Creates and returns a texture for a group of units.
 *
 *  \param game Pointer to the game instance.
 *
 *  \param type_var The unit variation representing the units' visuals type.
 *
 *  \param color_var The unit variation representing the units' color.
 *
 *  \return Returns ERR if an error occurred, or OK.
 *
 *  \sa create_units_texture()
 */
SDL_Texture* create_units_texture(Game* game, unit_var type_var, unit_var color_var);
