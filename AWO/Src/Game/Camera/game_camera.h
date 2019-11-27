#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/*! @brief The game camera module, holding the matrices used to transform vertices.
 */
typedef struct Game_Camera Game_Camera;

Game_Camera* create_game_camera(int window_width, int window_height);

void update_game_camera_view_position_to(Game_Camera* camera, float x, float y);
void update_game_camera_view_position(Game_Camera* camera, float added_x, float added_y);
void update_game_camera_view_zoom(Game_Camera* camera, float added_zoom);
void update_game_camera_view_zoom_to(Game_Camera* camera, float zoom);

void free_game_camera(Game_Camera* camera);