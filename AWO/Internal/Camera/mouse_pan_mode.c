#include "Camera/_camera.h"
#include "Input_State/Mouse_State/mouse_state.h"

void start_camera_mouse_pan_mode(Camera* camera, Mouse_State* mouse_state)
{
    camera->pan_x = camera->pan_y = 0;

    camera->pan_start_mouse_x = mouse_state->x;
    camera->pan_start_mouse_y = mouse_state->y;

    camera->pan_start_x = camera->x;
    camera->pan_start_y = camera->y;
}

Bool update_camera_mouse_pan_mode(Camera* camera, Mouse_State* mouse_state)
{
    if (
        mouse_state->x < 0 || 
        mouse_state->y < 0 || 
        mouse_state->x >* camera->window_width || 
        mouse_state->y >* camera->window_height
    ) {
        return FALSE;
    }

    camera->pan_x = mouse_state->x - camera->pan_start_mouse_x;
    camera->pan_y = mouse_state->y - camera->pan_start_mouse_y;

    update_game_camera_view_position_to(
        camera, 
        camera->pan_start_x + camera->pan_x, 
        camera->pan_start_y + camera->pan_y
    );

    return TRUE;
}
