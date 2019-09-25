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
static Uint8 current_input_state[KEY_COUNT];

void input_state_init()
{
    SDL_key_state = SDL_GetKeyboardState(NULL);

    // Initialize current input states to default
    for (int i = 0; i < KEY_COUNT; i++) {
        current_input_state[i] = BUTTON_STATE_DEFAULT;
    }
}

void input_state_update()
{
    // Update keyboard state
    SDL_PumpEvents();

    for (Key key = KEY_FIRST; key < KEY_COUNT; key++) {
        Uint8 pressed = SDL_key_state[keys_scancodes[key]];
        Uint8 old_key_state = current_input_state[key];

        // New state pressed
        if (pressed) {
            if (old_key_state == BUTTON_PRESSED || old_key_state == BUTTON_JUST_PRESSED) {
                current_input_state[key] = BUTTON_PRESSED;
            } else {
                current_input_state[key] = BUTTON_JUST_PRESSED;
            }

        // New state released
        }
        else {
            if (old_key_state == BUTTON_RELEASED || old_key_state == BUTTON_JUST_RELEASED) {
                current_input_state[key] = BUTTON_RELEASED;
            } else {
                current_input_state[key] = BUTTON_JUST_RELEASED;
            }
        }
    }
}

Button_State get_key_state(Key key)
{
    return current_input_state[key];
}
