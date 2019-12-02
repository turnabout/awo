#include <stdlib.h>

#include "conf.h"
#include "Game/Camera/_game_camera.h"

void zoom_camera_in(Game_Camera* camera, float zoom_value, float target_x, float target_y)
{
    // First update the view's zoom
    update_game_camera_view_zoom(camera, zoom_value);

    printf("view dimensions: {%.2f, %.2f}\n", camera->view_width, camera->view_width);
    // printf("target: {%.2f, %.2f}\n", target_x, target_y);

    // Set target

    /*
    target_x = (camera->view_width / 2);
    target_y = (camera->view_height / 2);

    // Update new view dimensions
    camera->view_width = camera->initial_view_width * camera->zoom;
    camera->view_height = camera->initial_view_height * camera->zoom;

    update_game_camera_view_position(
        camera, 
        target_x, 
        target_y
    );
*/

    // printf("{%.2f, %.2f}\n", camera->view_x, camera->view_y);


    // float new_target_x = target_x * camera->zoom;
    // float new_target_y = target_y * camera->zoom;



    /*
    // Get distance from target to origin
    float target_x_abs = fabs((double)(target_x - camera->view_x));
    float target_y_abs = fabs((double)(target_y - camera->view_y));

    // Find the proportional from the object to the origin
    float target_x_p = target_x_abs / camera->view_width;
    float target_y_p = target_y_abs / camera->view_height;

    // printf("{%.6f, %.6f}\n", camera->view_width, camera->view_height);

    // Calculate what the new distance from the target to the origin should be
    float target_x_new_abs = camera->view_width * target_x_p;
    float target_y_new_abs = camera->view_height * target_y_p;

    printf("{%.6f, %.6f}\n", target_x - target_x_new_abs, target_y - target_y_new_abs);

    // Set view coordinates based on where the object should be
    // uncomment this & test
    update_game_camera_view_position_to(
        camera, 
        target_x - target_x_new_abs, 
        target_y - target_y_new_abs
    );
    */


    // float real_value = (GLfloat)DEFAULT_TILE_SIZE * zoom_value;
    // float real_camera_zoom = (GLfloat)DEFAULT_TILE_SIZE * camera->zoom;



    /*
    printf(
        "(FROM: %.6f) -> (TO: %.6f)\n", 
        ((GLfloat)DEFAULT_TILE_SIZE) * camera->zoom,
        ((GLfloat)DEFAULT_TILE_SIZE) * (camera->zoom + zoom_value)
    );
    */

    // GLfloat diff = ((GLfloat)DEFAULT_TILE_SIZE) * (camera->zoom + zoom_value) - ((GLfloat)DEFAULT_TILE_SIZE) * camera->zoom;


    // printf("%.6f\n", diff);

    // update_game_camera_view_position(camera, diff, diff);

    // (GLfloat)DEFAULT_TILE_SIZE * camera->zoom


}

void zoom_camera_out(Game_Camera* camera, float value, float target_x, float target_y)
{
    update_game_camera_view_zoom(camera, -value);
}