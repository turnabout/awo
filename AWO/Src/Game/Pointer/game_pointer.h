#pragma once

#include "Game/Data/UI/UI_data.h"
#include "Game/Inputs/Mouse/mouse.h"
#include "Game/Camera/game_camera.h"
#include "Game/Renderer/game_renderer.h"

/*! @brief Pointer highlighting the tile currently hovered on by the player.
 */
typedef struct Game_Pointer Game_Pointer;

Game_Pointer* create_game_pointer(UI_Data* ui_data);
void update_pointer(Game_Pointer* pointer, Mouse_State* mouse, Game_Camera* camera);
void render_game_pointer(Game_Pointer* pointer, Game_Renderer* renderer);
void hide_game_pointer(Game_Pointer* pointer);
void free_game_pointer(Game_Pointer* pointer);
