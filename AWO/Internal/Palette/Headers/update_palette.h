#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Game_Data/game_data.h"

/*! @brief Updates the black pixel on the palette at the given index.
 *
 * Note: The palettes texture must be bound before calling this function.
 *
 *  @param[in] palette_index Index of the palette to update.
 *  @param[in] new_color Color to replace the current black pixel value with.
 */
void update_unit_palette_black_pixel(GLuint palette_index, GLubyte new_color);

/*! @brief Updates the currently active tile palette.
 *
 * Note: The game palettes texture must be bound before calling this function.
 *
 *  @param[in] weather The weather of the new active tile palette.
 */
void update_active_tile_palette(Weather weather, GLuint game_palette_tex, GLuint raw_palette_tex);

/*! @brief Updates the property palettes' weather colors to the currently active tile palette's.
 *
 *  @param[in] game_palette_texture The game palette texture.
 */
void update_properties_weather_colors(GLuint game_palette_texture);

/*! @brief Updates the player property palettes' current property lights color.
 *
 * By updating the palette directly, we can simulate the lights turning on and off.
 *
 *  @param[in] game_palette The game palette texture.
 *  @param[in] on Whether the lights new value should be "on".
 */
void update_game_palette_property_lights(GLuint game_palette, Bool on);