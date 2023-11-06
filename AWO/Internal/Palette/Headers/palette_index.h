#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Internal
#include "../../Player/player.h"

// Libs
#include "../../../Libs/Game_Data/game_data.h"

GLfloat get_active_tile_palette_index(Bool fog);
GLfloat get_player_unit_palette_index(Player_Index player_index, Bool done);
GLfloat get_player_property_palette_index(Player_Index player_index);
GLfloat get_fog_property_palette_index();

GLuint get_active_tile_palette_index_i(Bool fog);
GLuint get_player_unit_palette_index_i(Player_Index player_index, Bool done);
GLuint get_player_property_palette_index_i(Player_Index player_index);
GLuint get_fog_property_palette_index_i();