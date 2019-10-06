#pragma once
#include <SDL.h>

// List of every possible state for inputs
// State for a button
typedef enum {
    BUTTON_DOWN = 1 << 0, // Whether the button is pressed down
    BUTTON_JUST_CHANGED = 1 << 1, // Whether the button's pressed state was just changed
} Button_State;

#define BUTTON_STATE_DEFAULT 0

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

typedef struct Mouse_State {
    SDL_Point* pointer;
    Button_State buttons[MOUSE_BTN_COUNT];
    int in_window;
} Mouse_State;

// Initialize the input state module.
void input_state_init();

// Update the input state module.
void input_state_update();

// Gets the state of a single key.
Button_State get_key_state(Key key);

// Gets pointer to the mouse state.
Mouse_State* get_mouse_state();

// Gets whether a key was just pressed.
int key_pressed(Key key);

// Gets whether a key is being held down.
int key_down(Key key);

// Gets whether a click has just started.
int click_started(Mouse_State* mouse, Mouse_Button button);

// Gets whether a click is being held down.
int click_down(Mouse_State* mouse, Mouse_Button button);

// Gets whether a click has just ended.
int click_ended(Mouse_State* mouse, Mouse_Button button);
