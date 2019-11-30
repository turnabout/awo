#pragma once

/*! @brief The game camera module, holding the matrices used to transform vertices.
 */
typedef struct Game_Camera Game_Camera;

Game_Camera* create_game_camera(int window_width, int window_height);

void update_game_camera_view_position_to(Game_Camera* camera, float x, float y);
void update_game_camera_view_position(Game_Camera* camera, float added_x, float added_y);
void update_game_camera_view_zoom(Game_Camera* camera, float added_zoom);
void update_game_camera_view_zoom_to(Game_Camera* camera, float zoom);

// Initiate the camera's "mouse pan" mode, where the mouse is used to constantly update the current
// offset of the camera.
void start_camera_mouse_pan_mode(Game_Camera* camera);

void update_camera_mouse_pan_mode(Game_Camera* camera);

void end_camera_mouse_pan_mode(Game_Camera* camera);


void free_game_camera(Game_Camera* camera);