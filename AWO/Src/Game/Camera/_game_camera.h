#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include "conf.h"
#include "Game/Camera/game_camera.h"

struct Game_Camera {

    // Identity matrix reference.
    mat4 identity;

    // The game's view matrix.
    mat4 view;

    // The game's projection matrix.
    mat4 projection;

    // Current zoom value.
    float zoom;

    // Current camera view coordinate values.
    int x, y;

    // The mouse coordinate values when a mouse pan was initiated.
    int pan_start_mouse_x, pan_start_mouse_y;

    // The camera view coordinate values when a mouse pan was initiated.
    int pan_start_x, pan_start_y;

    // The current mouse pan offset coordinates.
    int pan_x, pan_y;

};

void update_game_camera_view_position_to(Game_Camera* camera, int x, int y);
void add_game_camera_view_position(Game_Camera* camera, int added_x, int added_y);
void update_game_camera_view_zoom_to(Game_Camera* camera, float zoom);
