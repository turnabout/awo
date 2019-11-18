#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cJSON.h>

#include "conf.h"
#include "Game/Data/Unit/enums.h"
#include "Game/Data/Tile/enums.h"
#include "Game/Data/Enums/weather.h"

/*! @brief Texture containing every row of palette data used during gameplay.
 *  Structure:
 *   0: Active Tile
 *   1: Active Tile (Fog)
 *   2: Player 0 Units
 *   3: Player 0 Units (Done)
 *   4: Player 1 Units
 *   5: Player 1 Units (Done)
 *   6: Player 2 Units
 *   7: Player 2 Units (Done)
 *   8: Player 3 Units
 *   9: Player 3 Units (Done)
 *  10: Player 0 Property
 *  11: Player 0 Property (Fog)
 *  12: Player 1 Property
 *  13: Player 1 Property (Fog)
 *  14: Player 2 Property
 *  15: Player 2 Property (Fog)
 *  16: Player 3 Property
 *  17: Player 3 Property (Fog)
 *  18: Player Neutral Property
 *  19: Player Neutral Property (Fog)
 */

/*! @brief Creates the palette texture used during a game.
 *
 * Holds the palette for the active weather and all active armies and properties.
 *
 *  @param[in] raw_palette_texture The texture of the raw palette.
 *  @param[in] active_weather The initial active weather of the game.
 *  @param[in] player_armies Array containing the army of each player. Non-existent armies must
 *  hold the value UNIT_VAR_NONE.
 */
GLuint create_game_palette_texture(
    GLuint raw_palette_texture, 
    Weather active_weather, 
    Unit_Variation player_armies[MAX_PLAYER_COUNT]
);

/*! @brief Updates the black pixel on the palette at the given index.
 *
 * Note: The palettes texture must be bound before calling this function.
 *
 *  @param[in] palette_index Index of the palette to update.
 *  @param[in] new_color Color to replace the current black pixel value with.
 */
void update_unit_palette_black_pixel(GLint palette_index, GLubyte new_color);

/*! @brief Updates the currently active tile palette.
 *
 * Note: The palettes texture must be bound before calling this function.
 *
 *  @param[in] weather The weather of the new active tile palette.
 */
void update_active_tile_palette(Weather weather);