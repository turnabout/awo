#include <stdlib.h>

#include "Game/Clock/Pub_Sub/_pub_sub.h"

struct Game_Clock_Pub_Sub {

    // List of subscriber modules registered to the pub-sub service.
    void* subscriber_modules[ANIMATION_CLOCK_COUNT];

    // List of all subscribers' callback functions.
    clock_subscriber_event_cb subscriber_callbacks[ANIMATION_CLOCK_COUNT];

};

void game_clock_pub_sub_nop(Tick_Event* tick_event, void* module){}

Game_Clock_Pub_Sub* create_clock_pub_sub()
{
    Game_Clock_Pub_Sub* service = (Game_Clock_Pub_Sub*)malloc(
        sizeof(Game_Clock_Pub_Sub)
    );

    // Initialize all subscriber modules & callbacks to empty values
    for (int i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
        service->subscriber_modules[i] = NULL;
        service->subscriber_callbacks[i] = game_clock_pub_sub_nop;
    }

    return service;
}

void register_clock_pub_sub_subscriber(
    Game_Clock_Pub_Sub* service,
    void* subscriber_module,
    clock_subscriber_event_cb subscriber_callback, 
    Animation_Clock_Index animation_clock
)
{
    service->subscriber_modules[animation_clock] = subscriber_module;
    service->subscriber_callbacks[animation_clock] = subscriber_callback;
}

void register_clock_pub_sub_tick_event(Game_Clock_Pub_Sub* service, Tick_Event* tick_event)
{
    service->subscriber_callbacks[tick_event->clock_index](
        tick_event,
        service->subscriber_modules[tick_event->clock_index]
    );
}

void free_clock_pub_sub(Game_Clock_Pub_Sub* service)
{
    free(service);
}
