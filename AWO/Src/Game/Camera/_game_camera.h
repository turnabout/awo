#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include "Game/Camera/game_camera.h"

#define DEFAULT_CAMERA_ZOOM 2.0f
#define DEFAULT_CAMERA_X 0.0f
#define DEFAULT_CAMERA_Y 0.0f

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
    float x, y;

    // The mouse coordinate values when a mouse pan was initiated.
    float pan_start_mouse_x, pan_start_mouse_y;

    // The camera view coordinate values when a mouse pan was initiated.
    float pan_start_x, pan_start_y;

    // The current mouse pan offset coordinates.
    float pan_x, pan_y;

};
