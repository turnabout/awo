#include <stdlib.h>
#include <cglm/cglm.h>

#include "conf.h"
#include "Game/Camera/_game_camera.h"
#include "Game/Renderer/game_renderer.h"

Game_Camera* create_game_camera(int window_width, int window_height)
{
    Game_Camera* camera = (Game_Camera*)malloc(sizeof(Game_Camera));

    glm_mat4_identity(camera->identity);

    // Set starting projection matrix
    glm_ortho(0.0f, (float)window_width, 0.0f, (float)window_height, -1.0f, 1.0f, camera->projection);
    update_game_renderer_matrix(camera->projection, "projection");

    // Set starting view matrix
    camera->x = DEFAULT_CAMERA_X;
    camera->y = DEFAULT_CAMERA_Y;

    update_game_camera_view_zoom_to(camera, DEFAULT_CAMERA_ZOOM);

    return camera;
}

void _refresh_game_camera(Game_Camera* camera)
{
    // Refresh position
    glm_translate_to(
        camera->identity,
        (vec3) { camera->x, camera->y, 0.0f },
        camera->view
    );

    // Refresh zoom
    glm_scale(
        camera->view,
        (vec3) { 
            (GLfloat)DEFAULT_TILE_SIZE * camera->zoom, 
            (GLfloat)DEFAULT_TILE_SIZE * camera->zoom, 
            1.0f 
        }
    );

    // Update other modules depending on the camera
    update_game_renderer_matrix(camera->view, "view");
}

void update_game_camera_view_position_to(Game_Camera* camera, float x, float y)
{
    camera->x = x;
    camera->y = y;
    _refresh_game_camera(camera);
}

void update_game_camera_view_position(Game_Camera* camera, float added_x, float added_y)
{
    camera->x += added_x;
    camera->y += added_y;
    _refresh_game_camera(camera);
}

void update_game_camera_view_zoom(Game_Camera* camera, float added_zoom)
{
    camera->zoom += added_zoom;
    _refresh_game_camera(camera);
}

void update_game_camera_view_zoom_to(Game_Camera* camera, float zoom)
{
    camera->zoom = zoom;
    _refresh_game_camera(camera);
}

void free_game_camera(Game_Camera* camera)
{
    free(camera);
}