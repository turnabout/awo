#pragma once

#include "Game/Data/UI/UI_data.h"
#include "Game/Inputs/Mouse/mouse.h"
#include "Game/Camera/game_camera.h"
#include "Game/Renderer/game_renderer.h"

/*! @brief Pointer highlighting the tile currently hovered on by the player.
 */
typedef struct Pointer Pointer;

Pointer* create_pointer(UI_Data* ui_data);
void free_pointer(Pointer* pointer);
