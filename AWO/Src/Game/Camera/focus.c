#include "Game/Camera/_game_camera.h"

void focus_camera(Game_Camera* camera, int target_x, int target_y)
{
    update_game_camera_view_position_to(
        camera, 
        target_x - (camera->subject_pixel_width / 2) ,
        target_y - (camera->subject_pixel_height / 2)
    );
}
