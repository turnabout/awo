#include <SDL.h>
#include "input_state.h"

#pragma warning( disable : 6011 )

// Keyboard state
// Array holding input state for every key used by the game
static Button_State keys_state[KEY_COUNT];

// Pointer to SDL Keyboard state array
const static Uint8* SDL_keyboard_state;

// Array of every SDL_Scancode corresponding to every key input used by the game
const static char keys_scancodes[KEY_COUNT] = {
    SDL_SCANCODE_1,
    SDL_SCANCODE_2,
    SDL_SCANCODE_3,
    SDL_SCANCODE_SPACE,
};

// Mouse state
// Array holding input state for every mouse button
struct Mouse_State* mouse_state;

// Bitmasks used to get the pressed/released bit of each mouse button
const static Uint32 SDL_mouse_bitmasks[MOUSE_BTN_COUNT] = { SDL_BUTTON_LEFT, SDL_BUTTON_RIGHT };

// Pointers storing mouse coordinates
static int* mouse_x, * mouse_y;

void input_state_init()
{
    SDL_keyboard_state = SDL_GetKeyboardState(NULL);

    // Initialize current key states to default
    for (int i = 0; i < KEY_COUNT; i++) {
        keys_state[i] = BUTTON_STATE_DEFAULT;
    }

    // Initialize mouse state to default
    mouse_state = (Mouse_State*)malloc(sizeof(Mouse_State));

    mouse_state->pointer = (SDL_Point*)malloc(sizeof(SDL_Point));
    mouse_state->pointer->x = mouse_state->pointer->y = 0;
    mouse_state->buttons[MOUSE_LEFT] = mouse_state->buttons[MOUSE_RIGHT] = BUTTON_STATE_DEFAULT;
}

void input_state_update()
{
    // Update keyboard state
    SDL_PumpEvents();

    for (Key key = KEY_FIRST; key < KEY_COUNT; key++) {

        // Get whether the key is currently pressed
        Uint8 current_pressed = SDL_keyboard_state[keys_scancodes[key]];

        // Get the previous state of this key
        Button_State previous_state = keys_state[key];

        // Bit 1: get the pressed status of the key
        // Bit 2: get whether the pressed status was changed from the previous state to this one
        keys_state[key] = 
            (current_pressed & BUTTON_PRESSED) |
            (previous_state ^ current_pressed) << 1;
    }

    // Update mouse state
    Uint32 sdl_mouse_state = SDL_GetMouseState(&mouse_state->pointer->x, &mouse_state->pointer->y);

    for (Mouse_Button btn = MOUSE_BTN_FIRST; btn < MOUSE_BTN_COUNT; btn++) {

        // Get whether the button is currently pressed
        // Right shift is to place the "pressed" value in the rightmost bit
        Uint32 current_pressed = sdl_mouse_state >> (SDL_mouse_bitmasks[btn] - 1);

        // Get the previous state of this button
        Uint8 previous_state = mouse_state->buttons[btn];

        // Store new state
        mouse_state->buttons[btn] = 
            (current_pressed & BUTTON_PRESSED) | 
            (previous_state ^ current_pressed) << 1;
    }
}

Button_State get_key_state(Key key)
{
    return keys_state[key];
}

Mouse_State* get_mouse_state()
{
    return mouse_state;
}

int key_pressed(Key key)
{
    Button_State toggle_btn_state = get_key_state(KEY_1); // TODO: Set elsewhere

    return (
        (keys_state[key] & BUTTON_PRESSED) && 
        (keys_state[key] & BUTTON_JUST_CHANGED)
    );
}

int click_started(Mouse_State* mouse, Mouse_Button button)
{
    return (
        (mouse->buttons[button] & BUTTON_PRESSED) &&
        (mouse->buttons[button] & BUTTON_JUST_CHANGED)
    );
}

int click_ended(Mouse_State* mouse, Mouse_Button button)
{
    return (
        !(mouse->buttons[button] & BUTTON_PRESSED) &&
        (mouse->buttons[button] & BUTTON_JUST_CHANGED)
    );
}
