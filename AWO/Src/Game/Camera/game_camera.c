#include <stdlib.h>
#include <cglm/cglm.h>

#include "conf.h"
#include "Utilities/utilities.h"
#include "Game/Camera/_game_camera.h"
#include "Game/Renderer/game_renderer.h"

Game_Camera* create_game_camera(
    int* window_width, 
    int* window_height, 
    int stage_tiles_width, 
    int stage_tiles_height
)
{
    Game_Camera* camera = (Game_Camera*)malloc(sizeof(Game_Camera));

    camera->window_width = window_width;
    camera->window_height = window_height;
    camera->loaded_stage_tiles_width = stage_tiles_width;
    camera->loaded_stage_tiles_height = stage_tiles_height;

    glm_mat4_identity(camera->identity);

    // Set starting projection matrix
    glm_ortho(0.0f, (float)*window_width, (float)*window_height, 0.0f, -1.0f, 1.0f, camera->projection);
    update_game_renderer_matrix(camera->projection, "projection");

    // Set starting view matrix
    camera->x = DEFAULT_CAMERA_X;
    camera->y = DEFAULT_CAMERA_Y;

    update_game_camera_view_zoom_to(camera, DEFAULT_CAMERA_ZOOM);

    // Initially center the camera in the middle of the window
    focus_camera(camera, *camera->window_width / 2, *camera->window_height / 2);

    return camera;
}

void _refresh_game_camera(Game_Camera* camera)
{
    // Refresh position
    glm_translate_to(
        camera->identity,
        (vec3) { (float)camera->x, (float)camera->y, 0.0f },
        camera->view
    );

    // Refresh zoom
    glm_scale(
        camera->view,
        (vec3) { camera->zoom, camera->zoom, 1.0f }
    );

    // Update other modules depending on the camera
    update_game_renderer_matrix(camera->view, "view");
}

void update_game_camera_view_position_to(Game_Camera* camera, int x, int y)
{
    camera->x = x;
    camera->y = y;
    _refresh_game_camera(camera);
}

void add_game_camera_view_position(Game_Camera* camera, int added_x, int added_y)
{
    camera->x += added_x;
    camera->y += added_y;
    _refresh_game_camera(camera);
}

void update_game_camera_view_zoom_to(Game_Camera* camera, float zoom)
{
    camera->zoom = zoom;
    _refresh_game_camera(camera);

    // Update the loaded stage's dimensions
    camera->loaded_stage_width = round_float_to_int(
        camera->zoom * camera->loaded_stage_tiles_width
    );

    camera->loaded_stage_height = round_float_to_int(
        camera->zoom * camera->loaded_stage_tiles_height
    );
}

void free_game_camera(Game_Camera* camera)
{
    if (camera != NULL) {
        free(camera);
    }
}
