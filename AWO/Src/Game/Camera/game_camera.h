#pragma once

#include "types.h"
#include "Game/Inputs/inputs.h"
#include "Game/Stage/stage.h"
#include "Game/Renderer/game_renderer.h"

/*! @brief The game camera module, holding the matrices used to transform vertices.
 */
typedef struct Game_Camera Game_Camera;

Game_Camera* create_game_camera(
    int* window_width,
    int* window_height,
    int subject_width,
    int subject_height
);

void zoom_game_camera(Game_Camera* camera, float value, int target_x, int target_y);

// Initiates the camera's "mouse pan" mode, where the mouse is used to constantly update the current
// offset of the camera.
void start_camera_mouse_pan_mode(Game_Camera* camera, Mouse_State* mouse_state);

// Centers the camera on the given point.
void focus_camera(Game_Camera* camera, int target_x, int target_y);

/*! @brief Gets the grid coordinates of the subject at the given absolute screen coordinates.
 *
 *  @param[in] camera The game camera module.
 *  @param[in] abs_x The absolute screen X coordinate used to search for relative coordinates.
 *  @param[in] abs_y The absolute screen Y coordinate used to search for relative coordinates.
 *  @param[out] relative_x Set to the grid's X relative coordinate, if found.
 *  @param[out] relative_y Set to the grid's Y relative coordinate, if found.
 *  @return Whether a grid tile was found at the given absolute coordinates.
 */
Bool get_subject_grid_coordinates(
    Game_Camera* camera,
    int abs_x,
    int abs_y,
    int* relative_x,
    int* relative_y
);

Bool update_camera_mouse_pan_mode(Game_Camera* camera, Mouse_State* mouse_state);

void free_game_camera(Game_Camera* camera);