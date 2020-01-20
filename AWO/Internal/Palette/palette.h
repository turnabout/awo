#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Config/config.h"
#include "Player/player.h"
#include "Game_Data/game_data.h"
#include "Headers/palette_index.h"
#include "Headers/update_palette.h"

/*! @brief Creates the palette texture used during a game.
 *
 *  @note Holds the palette for the game's tileset using the active weather, and all active armies 
 *  and properties.
 *
 *  @param[in] palette_data The palette data module.
 *  @param[in] active_weather The initial active weather of the game.
 *  @param[in] player_armies Array containing the army of each player. Non-existent armies must
 *  hold the value UNIT_VAR_NONE.
 *  @return The created palette GL texture.
 */
GLuint create_game_palette_texture(
    Palette_Data* palette_data,
    Weather active_weather,
    Army_Type player_armies[MAX_PLAYER_COUNT]
);