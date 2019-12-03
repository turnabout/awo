#include <stdlib.h>

#include "conf.h"
#include "Utilities/utilities.h"
#include "Game/Camera/_game_camera.h"
#include "Game/Inputs/inputs.h"

void zoom_game_camera(Game_Camera* camera, float zoom_value, int target_x, int target_y)
{
    // Get percentage increase of zoom
    float original_zoom = camera->zoom;
    float new_zoom = camera->zoom + zoom_value;

    float zoom_increase = new_zoom - original_zoom;
    float zoom_percent_increase = zoom_increase / original_zoom;

    printf("%.2f -> %.2f (%.8f increase)\n", original_zoom, new_zoom, zoom_percent_increase);

    // Internally update the camera's zoom
    add_game_camera_view_zoom(camera, zoom_value);

    // Get diff between camera's current coordinates and the target's coordinates
    int diff_x = camera->x - target_x;
    int diff_y = camera->y - target_y;

    // Calculate coordinates of position adjustment
    int adjust_x = round_float_to_int((float)diff_x * zoom_percent_increase);
    int adjust_y = round_float_to_int((float)diff_y * zoom_percent_increase);

    printf("%d, %d\n", adjust_x, adjust_y);

    int old_x = camera->x;
    int old_y = camera->y;

    add_game_camera_view_position(camera, adjust_x, adjust_y);

    printf("adjust: {%d, %d}\n", adjust_x, adjust_y);
    printf("{%d, %d} -> {%d, %d}\n\n", old_x, old_y, camera->x, camera->y);
}

void zoom_camera_out(Game_Camera* camera, float value, float target_x, float target_y)
{
    add_game_camera_view_zoom(camera, -value);
}