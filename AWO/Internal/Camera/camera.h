#pragma once

/*! @brief The camera module used for keeping track of the game's pan coordinates & zoom level.
 */
typedef struct Camera Camera;

Camera* create_game_camera(
    int* window_width,
    int* window_height,
    int subject_width,
    int subject_height
);

void zoom_game_camera(Camera* camera, float value, int target_x, int target_y);

// Centers the camera on the given point.
void focus_camera(Camera* camera, int target_x, int target_y);

void free_game_camera(Camera* camera);

// Initiates the camera's "mouse pan" mode, where the mouse is used to constantly update the current
// offset of the camera.
// void start_camera_mouse_pan_mode(Camera* camera, Mouse_State* mouse_state);

/*! @brief Gets the grid coordinates of the subject at the given absolute screen coordinates.
 *
 *  @param[in] camera The game camera module.
 *  @param[in] abs_x The absolute screen X coordinate used to search for relative coordinates.
 *  @param[in] abs_y The absolute screen Y coordinate used to search for relative coordinates.
 *  @param[out] relative_x Set to the grid's X relative coordinate, if found.
 *  @param[out] relative_y Set to the grid's Y relative coordinate, if found.
 *  @return Whether a grid tile was found at the given absolute coordinates.
 */
/*
Bool get_subject_grid_coordinates(
    Camera* camera,
    int abs_x,
    int abs_y,
    int* relative_x,
    int* relative_y
);
*/

// Bool update_camera_mouse_pan_mode(Camera* camera, Mouse_State* mouse_state);