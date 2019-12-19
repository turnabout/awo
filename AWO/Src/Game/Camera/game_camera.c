#include <stdlib.h>
#include <cglm/cglm.h>

#include "conf.h"
#include "Utilities/utilities.h"
#include "Game/Camera/_game_camera.h"

Game_Camera* create_game_camera(
    Game_Renderer* game_renderer, 
    int* window_width, 
    int* window_height, 
    Stage* stage
)
{
    Game_Camera* camera = malloc(sizeof(Game_Camera));

    camera->game_renderer = game_renderer;
    camera->window_width = window_width;
    camera->window_height = window_height;
    camera->subject = stage;

    // Set starting view matrix
    camera->x = DEFAULT_CAMERA_X;
    camera->y = DEFAULT_CAMERA_Y;

    update_game_camera_view_zoom_to(camera, DEFAULT_CAMERA_ZOOM);

    // Initially center the camera in the middle of the window
    focus_camera(camera, *camera->window_width / 2, *camera->window_height / 2);

    return camera;
}

void inline send_game_camera_updated_values(Game_Camera* camera)
{
    update_game_renderer_view_matrices(
        camera->game_renderer,
        camera->x,
        camera->y,
        camera->zoom
    );
}

void update_game_camera_view_position_to(Game_Camera* camera, int x, int y)
{
    camera->x = x;
    camera->y = y;
    send_game_camera_updated_values(camera);
}

void add_game_camera_view_position(Game_Camera* camera, int added_x, int added_y)
{
    camera->x += added_x;
    camera->y += added_y;
    send_game_camera_updated_values(camera);
}

void update_game_camera_view_zoom_to(Game_Camera* camera, float zoom)
{
    camera->zoom = zoom;
    send_game_camera_updated_values(camera);

    // Update the dimensions of the camera subject
    camera->subject_pixel_width = round_float_to_int(
        camera->zoom * camera->subject->width
    );

    camera->subject_pixel_height = round_float_to_int(
        camera->zoom * camera->subject->height
    );
}

void free_game_camera(Game_Camera* camera)
{
    if (camera != NULL) {
        free(camera);
    }
}
