#pragma once

#include <cglm/cglm.h>

#include "Camera/camera.h"
#include "Utilities/utilities.h"

struct Camera {

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

    // Pointers to the window dimensions.
    int* window_width, * window_height;

    // The camera's subject dimensions (at 1x zoom).
    int subject_width, subject_height;

    // Actual visible dimensions of the camera's subject (currently loaded stage), in pixels.
    int subject_pixel_width, subject_pixel_height;

};

void update_game_camera_view_position_to(Camera* camera, int x, int y);
void add_game_camera_view_position(Camera* camera, int added_x, int added_y);
void update_game_camera_view_zoom_to(Camera* camera, float zoom);
