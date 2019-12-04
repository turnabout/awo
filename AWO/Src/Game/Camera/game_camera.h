#pragma once

#include "types.h"

/*! @brief The game camera module, holding the matrices used to transform vertices.
 */
typedef struct Game_Camera Game_Camera;

Game_Camera* create_game_camera(int window_width, int window_height);

void zoom_game_camera(Game_Camera* camera, float value, int target_x, int target_y);

// Initiate the camera's "mouse pan" mode, where the mouse is used to constantly update the current
// offset of the camera.
void start_camera_mouse_pan_mode(Game_Camera* camera);

Bool update_camera_mouse_pan_mode(Game_Camera* camera);

void end_camera_mouse_pan_mode(Game_Camera* camera);


void free_game_camera(Game_Camera* camera);