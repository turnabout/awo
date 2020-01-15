#pragma once

#include <cglm/cglm.h>

#include "Camera/camera.h"
#include "Utilities/utilities.h"
#include "Config/config.h"

// Game Camera
#define DEFAULT_CAMERA_ZOOM (DEFAULT_ENTITY_SIZE * 2)
#define DEFAULT_CAMERA_X 0
#define DEFAULT_CAMERA_Y 0

#define MIN_ZOOM_VALUE 16.0f
#define MAX_ZOOM_VALUE 40.0f

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
void update_game_camera_view_zoom_to(Camera* camera, float zoom);
