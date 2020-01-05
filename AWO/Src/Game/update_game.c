#include "Game/_game.h"

#define MODE_NORMAL 0
#define MODE_FREEZE 1

#define CONTROL_MODE_NORMAL 0
#define CONTROL_MODE_PAN    1

static int game_mode = MODE_NORMAL;
static int control_mode = CONTROL_MODE_NORMAL;

void update_game(Game* game, float delta_time)
{

    update_keyboard_state();
    update_mouse_module_state();

    if (game_mode == MODE_FREEZE) {
        if (get_key_state(KEY_1) == BUTTON_DOWN_START) {
            game_mode = MODE_NORMAL;
        } else {
            return;
        }
    }

    if (get_key_state(KEY_2) == BUTTON_DOWN_START) {
        game_mode = MODE_FREEZE;
    }

    update_game_clock(game->clock, delta_time);
    update_game_board(game->board);

    // Update panning
    if (control_mode == CONTROL_MODE_PAN) {
        

        // End "pan" control mode
        if (
            !update_camera_mouse_pan_mode(game->camera, game->mouse_state) ||
            get_key_state(KEY_SPACE) == BUTTON_UP || 
            game->mouse_state->buttons[MOUSE_BUTTON_LEFT] == BUTTON_UP
        ) {
            control_mode = CONTROL_MODE_NORMAL;
        }

    } else if (control_mode == CONTROL_MODE_NORMAL) {
    
        // Start "pan" control mode
        if (
            get_key_state(KEY_SPACE) == BUTTON_DOWN &&
            game->mouse_state->buttons[MOUSE_BUTTON_LEFT] == BUTTON_DOWN_START
        ) {
            start_camera_mouse_pan_mode(game->camera, game->mouse_state);
            control_mode = CONTROL_MODE_PAN;
        }

        // Zoom at mouse coordinates if mouse wheel was scrolled
        if (game->mouse_state->scroll) {
            zoom_game_camera(
                game->camera, 
                game->mouse_state->scroll, 
                game->mouse_state->x, 
                game->mouse_state->y
            );
        }
    }

    if (control_mode == CONTROL_MODE_NORMAL) {
        update_cursor(game->cursor, game->mouse_state, game->camera);

        update_game_editor(
            game->editor, 
            game->renderer,
            game->board,
            game->clock,
            game->cursor,
            game->mouse_state
        );
    }
}