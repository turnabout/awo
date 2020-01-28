#include "Input_Handlers/Mouse_Handler/mouse_handler.h"
#include "Input_State/Mouse_State/mouse_state.h"

#define MAX_MOUSE_EVENTS 10

typedef struct Mouse_Scroll_Event {

    // The added horizontal and vertical scroll values.
    float x, y;

} Mouse_Scroll_Event;

struct Mouse_Handler {

    // Reference to the game window.
    GLFWwindow* glfw_window;

    // Mouse scroll events queued up & ready to be processed w/ amounts
    Mouse_Scroll_Event scroll_events[MAX_MOUSE_EVENTS];
    int scroll_events_count;

    // Mouse coordinates
    int x, y;

};