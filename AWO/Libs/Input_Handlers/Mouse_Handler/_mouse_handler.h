#include "Input_Handlers/Mouse_Handler/mouse_handler.h"
#include "Input_State/Mouse_State/mouse_state.h"

#define MAX_MOUSE_EVENTS 10

typedef struct Mouse_Move_Event {

    // The mouse movement x/y
    int x, y;

} Mouse_Move_Event;

typedef struct Mouse_Scroll_Event {

    // The added vertical scroll value
    float vertical_scroll;

    // The added horizontal scroll value
    float horizontal_scroll;

} Mouse_Scroll_Event;

struct Mouse_Handler {

    // Reference to the game window.
    Game_Window* game_window;

    // Mouse events queued up & ready to be processed w/ amounts
    Mouse_Scroll_Event scroll_events[MAX_MOUSE_EVENTS];
    int scroll_events_count;

    Mouse_Move_Event move_events[MAX_MOUSE_EVENTS];
    int move_events_count;

};