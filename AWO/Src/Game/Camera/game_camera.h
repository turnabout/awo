#pragma once

#include "types.h"
#include "Game/Inputs/inputs.h"
#include "Game/Stage/stage.h"

/*! @brief The game camera module, holding the matrices used to transform vertices.
 */
typedef struct Game_Camera Game_Camera;

Game_Camera* create_game_camera(int* window_width, int* window_height, Stage* stage);

void zoom_game_camera(Game_Camera* camera, float value, int target_x, int target_y);

// Initiates the camera's "mouse pan" mode, where the mouse is used to constantly update the current
// offset of the camera.
void start_camera_mouse_pan_mode(Game_Camera* camera, Mouse_State* mouse_state);

// Centers the camera on the given point.
void focus_camera(Game_Camera* camera, int target_x, int target_y);

// Gets the camera subject tile present at the given absolute screen coordinates, if any.
// Returns the tile's x/y relative coordinates.
// Both set to -1 if no tile was found at the given absolute coordinates.
Bool get_subject_tile_by_coordinates(
    Game_Camera* camera,
    int abs_x,
    int abs_y,
    int* relative_x,
    int* relative_y
);

Bool update_camera_mouse_pan_mode(Game_Camera* camera, Mouse_State* mouse_state);

void free_game_camera(Game_Camera* camera);