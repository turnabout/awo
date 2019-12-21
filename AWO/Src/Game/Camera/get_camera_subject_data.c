#include <math.h>

#include "Game/Camera/_game_camera.h"

Bool get_subject_grid_coordinates(
    Game_Camera* camera, 
    int abs_x, 
    int abs_y, 
    int* relative_x, 
    int* relative_y
)
{
    // Return false if the absolute coordinates aren't within the subject
    if (
        abs_x < camera->x ||
        abs_y < camera->y ||
        abs_x >= camera->x + (camera->subject_pixel_width) ||
        abs_y >= camera->y + (camera->subject_pixel_height)
    ) {
        return FALSE;
    }

    // Get the offset of the given absolute coordinates within the camera subject
    int offset_x = abs_x - camera->x;
    int offset_y = abs_y - camera->y;

    // Apply camera zoom to get which tile of the subject is at the absolute coordinates
    *relative_x = (int)((float)offset_x / camera->zoom);
    *relative_y = (int)((float)offset_y / camera->zoom);

    return TRUE;
}