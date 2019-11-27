#include <stdlib.h>
#include <cglm/cglm.h>

#include "conf.h"
#include "Game/Camera/game_camera.h"
#include "Game/Renderer/game_renderer.h"

struct Game_Camera {

    // Identity matrix reference.
    mat4 identity;

    // The game's view matrix.
    mat4 view;

    // The game's projection matrix.
    mat4 projection;

};

Game_Camera* create_game_camera(int window_width, int window_height)
{
    Game_Camera* camera = (Game_Camera*)malloc(sizeof(Game_Camera));

    glm_mat4_identity(camera->identity);

    // Set starting view matrix
    glm_scale_to(
        camera->identity,
        (vec3) { (GLfloat)DEFAULT_TILE_SIZE * 2, (GLfloat)DEFAULT_TILE_SIZE * 2, 1.0f },
        camera->view
    );

    // Set starting projection matrix
    // glm_mat4_identity(camera->projection);
    glm_ortho(
        0.0f, 
        (float)window_width, 
        0.0f, 
        (float)window_height, 
        -1.0f, 
        1.0f, 
        camera->projection
    );

    update_game_renderer_matrix(camera->projection, "projection");
    update_game_renderer_matrix(camera->view, "view");

    return camera;
}

void update_game_camera_view_position(Game_Camera* camera, float added_x, float added_y)
{

}

void update_game_camera_view_zoom(Game_Camera* camera, float added_value)
{
}

void free_game_camera(Game_Camera* camera)
{
    free(camera);
}
