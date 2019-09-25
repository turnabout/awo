#include <SDL.h>
#include "input_state.h"

#pragma warning( disable : 6011 )

// Array of every corresponding SDL_Scancode to every key input used by the game
const static char keys_scancodes[] = {
    SDL_SCANCODE_1,
    SDL_SCANCODE_2,
    SDL_SCANCODE_3,
    SDL_SCANCODE_SPACE,
};

// Current result stored at SDL_GetKeyboardState pointer
const static Uint8* SDL_key_state;

// Array holding input state for every key used by the game
static Button_State current_key_state[KEY_COUNT];

// Current mouse state
static Button_State current_mouse_state[MOUSE_BTN_COUNT] = {
    BUTTON_RELEASED,
    BUTTON_RELEASED,
};

static int* mouse_x;
static int* mouse_y;

const static Uint32 mouse_sdl_buttons[MOUSE_BTN_COUNT] = {
    SDL_BUTTON_LEFT,
    SDL_BUTTON_RIGHT,
};

void input_state_init()
{
    SDL_key_state = SDL_GetKeyboardState(NULL);

    // Initialize current input states to default
    for (int i = 0; i < KEY_COUNT; i++) {
        current_key_state[i] = BUTTON_STATE_DEFAULT;
    }

    mouse_x = malloc(sizeof(int));
    mouse_y = malloc(sizeof(int));
}

void input_state_update()
{
    // Update keyboard state
    SDL_PumpEvents();

    for (Key key = KEY_FIRST; key < KEY_COUNT; key++) {
        Uint8 pressed = SDL_key_state[keys_scancodes[key]];
        Button_State old_key_state = current_key_state[key];

        // New state pressed
        if (pressed) {
            if (old_key_state == BUTTON_PRESSED || old_key_state == BUTTON_JUST_PRESSED) {
                current_key_state[key] = BUTTON_PRESSED;
            } else {
                current_key_state[key] = BUTTON_JUST_PRESSED;
            }

        // New state released
        }
        else {
            if (old_key_state == BUTTON_RELEASED || old_key_state == BUTTON_JUST_RELEASED) {
                current_key_state[key] = BUTTON_RELEASED;
            } else {
                current_key_state[key] = BUTTON_JUST_RELEASED;
            }
        }
    }

    // Update mouse state
    Uint32 sdl_mouse_state = SDL_GetMouseState(mouse_x, mouse_y);

    for (Mouse_Button btn = MOUSE_BTN_FIRST; btn < MOUSE_BTN_COUNT; btn++) {

        // Get whether the button is currently pressed
        Uint32 pressed = sdl_mouse_state & SDL_BUTTON(mouse_sdl_buttons[btn]);
        Uint8 old_mouse_state = current_mouse_state[btn];

        // New state pressed
        if (pressed) {
            if (old_mouse_state == BUTTON_PRESSED || old_mouse_state == BUTTON_JUST_PRESSED) {
                current_mouse_state[btn] = BUTTON_PRESSED;
            } else {
                current_mouse_state[btn] = BUTTON_JUST_PRESSED;
            }

        // New state released
        }
        else {
            if (old_mouse_state == BUTTON_RELEASED || old_mouse_state == BUTTON_JUST_RELEASED) {
                current_mouse_state[btn] = BUTTON_RELEASED;
            } else {
                current_mouse_state[btn] = BUTTON_JUST_RELEASED;
            }
        }
    }
}

Button_State get_key_state(Key key)
{
    return current_key_state[key];
}

Button_State get_mouse_state(Mouse_Button btn)
{
    return current_mouse_state[btn];
}

void get_mouse_coordinates(int* x, int* y)
{
    *x = *mouse_x;
    *y = *mouse_y;
}
