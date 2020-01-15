#pragma once

/*! @brief Every possible state for a button.
 *
 * Button states are represented by a simple 2-bit digit.
 * The first bit determines whether the key is pressed down.
 * The second bit determines whether the key was just changed this frame.
 */
typedef enum Button_State {
    BUTTON_UP         = 0,
    BUTTON_DOWN       = 1,
    BUTTON_UP_START   = 2,
    BUTTON_DOWN_START = 3,
} Button_State;