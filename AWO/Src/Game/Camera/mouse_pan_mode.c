#include "Game/Camera/_game_camera.h"
#include "Game/Inputs/inputs.h"

/*
void camera_mouse_pan_cb(GLFWwindow* window, double x, double y)
{

    // mouse_x = (int)x;

    // Subtract the current game window tiles_height from the mouse position to get the Y coordinate 
    // relative to the lower edge instead of the upper edge.
    // mouse_y = abs((int)y - *game_window_height);
}
*/

void start_camera_mouse_pan_mode(Game_Camera* camera)
{
    get_mouse_position(&camera->pan_start_mouse_x, &camera->pan_start_mouse_y);

    camera->pan_x = camera->pan_y = 0;

    camera->pan_start_x = camera->x;
    camera->pan_start_y = camera->y;
}

Bool update_camera_mouse_pan_mode(Game_Camera* camera)
{
    int mouse_x, mouse_y;

    get_mouse_position(&mouse_x, &mouse_y);

    if (
        mouse_x < 0 || 
        mouse_y < 0 || 
        mouse_x >* camera->window_width || 
        mouse_y >* camera->window_height
    ) {
        return FALSE;
    }

    camera->pan_x = mouse_x - camera->pan_start_mouse_x;
    camera->pan_y = mouse_y - camera->pan_start_mouse_y;

    update_game_camera_view_position_to(
        camera, 
        camera->pan_start_x + camera->pan_x, 
        camera->pan_start_y + camera->pan_y
    );

    return TRUE;
}
