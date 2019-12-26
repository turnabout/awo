#include <stdlib.h>

#include "Game/Clock/Pub_Sub/_pub_sub.h"

struct Game_Clock_Pub_Sub {

    // List of subscriber modules registered to the pub-sub.
    void* subscriber_modules[ANIMATION_CLOCK_COUNT];

    // List of all subscribers' callback functions.
    clock_subscriber_event_cb subscriber_callbacks[ANIMATION_CLOCK_COUNT];

};

void game_clock_pub_sub_nop(Tick_Event* tick_event, void* module){}

Game_Clock_Pub_Sub* create_clock_pub_sub()
{
    Game_Clock_Pub_Sub* pub_sub = (Game_Clock_Pub_Sub*)malloc(
        sizeof(Game_Clock_Pub_Sub)
    );

    // Initialize all subscriber modules & callbacks to empty values
    for (int i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
        pub_sub->subscriber_modules[i] = NULL;
        pub_sub->subscriber_callbacks[i] = game_clock_pub_sub_nop;
    }

    return pub_sub;
}

void register_clocks_pub_sub_subscriber(
    Game_Clock_Pub_Sub* pub_sub,
    void* subscriber_module,
    clock_subscriber_event_cb subscriber_callback, 
    Animation_Clock_Index clocks[ANIMATION_CLOCK_COUNT],
    int clocks_count
)
{
    for (int i = 0; i < clocks_count; i++) {
        pub_sub->subscriber_modules[clocks[i]] = subscriber_module;
        pub_sub->subscriber_callbacks[clocks[i]] = subscriber_callback;
    }
}

void process_clock_pub_sub_tick_event(Game_Clock_Pub_Sub* pub_sub, Tick_Event* tick_event)
{
    pub_sub->subscriber_callbacks[tick_event->timer_index](
        tick_event,
        pub_sub->subscriber_modules[tick_event->timer_index]
    );
}

void free_clock_pub_sub(Game_Clock_Pub_Sub* pub_sub)
{
    if (pub_sub != NULL) {
        free(pub_sub);
    }
}
