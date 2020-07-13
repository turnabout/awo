#include "Camera/_camera.h"

void zoom_game_camera(Camera* camera, float zoom_value, int target_x, int target_y)
{
    // Get percentage increase of zoom
    float original_zoom = camera->zoom;
    float new_zoom = camera->zoom + zoom_value;

    // Clamp new zoom between minimum/maximum values
    if (new_zoom <= MIN_ZOOM_VALUE || new_zoom >= MAX_ZOOM_VALUE) {

        new_zoom = (new_zoom <= MIN_ZOOM_VALUE) ? MIN_ZOOM_VALUE : MAX_ZOOM_VALUE;

        // Don't bother updating if new clamped zoom value is same as the old one
        if (new_zoom == original_zoom) {
            return;
        }
    }

    float zoom_increase = new_zoom - original_zoom;
    float zoom_percent_increase = zoom_increase / original_zoom;

    // Internally update the camera's zoom
    update_game_camera_view_zoom_to(camera, new_zoom);

    // Get diff between camera's current coordinates and the target's coordinates
    int diff_x = camera->x - target_x;
    int diff_y = camera->y - target_y;

    // Calculate coordinates of position adjustment & add to camera position
    update_game_camera_view_position_to(
        camera, 
        camera->x + round_float_to_int((float)diff_x * zoom_percent_increase), 
        camera->y + round_float_to_int((float)diff_y * zoom_percent_increase)
    );
}