#pragma once
#include <SDL.h>

// List of every possible state for inputs
typedef enum {
    BUTTON_RELEASED,      // Button is released
    BUTTON_JUST_RELEASED, // Button was just released this frame
    BUTTON_PRESSED,       // Button is pressed down
    BUTTON_JUST_PRESSED,  // Button was just pressed down this frame
} Button_State;

#define BUTTON_STATE_DEFAULT BUTTON_RELEASED

// List of every key input used by the game
typedef enum {
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_SPACE,
} Key;

#define KEY_FIRST KEY_1
#define KEY_LAST  KEY_SPACE
#define KEY_COUNT KEY_LAST + 1

typedef enum {
    MOUSE_LEFT,
    MOUSE_RIGHT,
} Mouse_Button;

#define MOUSE_BTN_FIRST MOUSE_LEFT
#define MOUSE_BTN_LAST  MOUSE_RIGHT
#define MOUSE_BTN_COUNT MOUSE_BTN_LAST + 1

// Initialize the input state module.
void input_state_init();

// Update the input state module.
void input_state_update();

// Gets the state for a single key.
Button_State get_key_state(Key key);

// Gets the current button state for a mouse button.
Button_State get_mouse_state(Mouse_Button btn);

// Stores current mouse coordinates in x and y.
void get_mouse_coordinates(int* x, int* y);
