#include <stdlib.h>

#include "Camera/_camera.h"

Camera* create_game_camera(
    int* window_width, 
    int* window_height,
    int subject_width,
    int subject_height
)
{
    Camera* camera = malloc(sizeof(Camera));

    camera->window_width = window_width;
    camera->window_height = window_height;
    camera->subject_width = subject_width;
    camera->subject_height = subject_height;

    // Set starting view matrix
    camera->x = DEFAULT_CAMERA_X;
    camera->y = DEFAULT_CAMERA_Y;

    update_game_camera_view_zoom_to(camera, DEFAULT_CAMERA_ZOOM);

    // Initially center the camera in the middle of the window
    focus_camera(camera, *camera->window_width / 2, *camera->window_height / 2);

    return camera;
}

static void inline send_game_camera_updated_values(Camera* camera)
{
    /*
    update_game_renderer_view_matrices(
        camera->game_renderer,
        camera->x,
        camera->y,
        camera->zoom
    );
    */
}

void update_game_camera_view_position_to(Camera* camera, int x, int y)
{
    camera->x = x;
    camera->y = y;
    send_game_camera_updated_values(camera);
}

void update_game_camera_view_zoom_to(Camera* camera, float zoom)
{
    camera->zoom = zoom;
    send_game_camera_updated_values(camera);

    // Update the dimensions of the camera subject
    camera->subject_pixel_width = round_float_to_int(
        camera->zoom * camera->subject_width
    );

    camera->subject_pixel_height = round_float_to_int(
        camera->zoom * camera->subject_height
    );
}

void free_game_camera(Camera* camera)
{
    if (camera != NULL) {
        free(camera);
    }
}
