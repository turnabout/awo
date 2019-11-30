#include "Game/_game.h"

#define CONTROL_MODE_NORMAL 0
#define CONTROL_MODE_PAN    1

static int control_mode = CONTROL_MODE_NORMAL;

void update_game(Game* game, float delta_time)
{
    update_keys_state();
    update_mouse_buttons_state();

    update_game_clock(game->clock, delta_time);
    update_game_board(game->board);


    // Update panning
    if (control_mode == CONTROL_MODE_PAN) {
        update_camera_mouse_pan_mode(game->camera);

        // End "pan" control mode
        if (
            get_key_state(KEY_SPACE) == BUTTON_UP || 
            get_mouse_button_state(MOUSE_BUTTON_LEFT) == BUTTON_UP
        ) {
            end_camera_mouse_pan_mode(game->camera);
            control_mode = CONTROL_MODE_NORMAL;
        }


    } else if (
        control_mode == CONTROL_MODE_NORMAL && 
        get_key_state(KEY_SPACE) == BUTTON_DOWN && 
        get_mouse_button_state(MOUSE_BUTTON_LEFT) == BUTTON_DOWN
    ) {
        // Start "pan" control mode
        start_camera_mouse_pan_mode(game->camera);
        control_mode = CONTROL_MODE_PAN;


        // update_game_camera_view_zoom(game->camera, 0.5f);
    }




    // glfwSetScrollCallback(GLFWwindow* window, GLFWscrollfun cbfun);


    if (get_key_state(KEY_UP) == BUTTON_DOWN_START) {
        update_game_camera_view_zoom(game->camera, 0.5f);
    }

    if (get_key_state(KEY_DOWN) == BUTTON_DOWN_START) {
        update_game_camera_view_zoom(game->camera, -0.5f);
    }

    if (get_key_state(KEY_W) == BUTTON_DOWN) {
        update_game_camera_view_position(game->camera, 0.0f, -3.0f);
    }

    if (get_key_state(KEY_S) == BUTTON_DOWN) {
        update_game_camera_view_position(game->camera, 0.0f, 3.0f);
    }




    if (get_key_state(KEY_A) == BUTTON_DOWN_START) {
        update_game_camera_view_position(game->camera, 1.0f, 0.0f);
    }

    if (get_key_state(KEY_D) == BUTTON_DOWN_START) {
        update_game_camera_view_position(game->camera, -1.0f, 0.0f);
    }
}