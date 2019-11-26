#include <stdlib.h>

#include "Game/Clock/Pub_Sub_Service/_pub_sub_service.h"

struct Game_Clock_Pub_Sub_Service {

    // List of all subscribers' callback functions.
    clock_subscriber_event_cb subscriber_callbacks[ANIMATION_CLOCK_COUNT];

};

void game_clock_pub_sub_nop(Tick_Event* tick_event){}

Game_Clock_Pub_Sub_Service* create_pub_sub_service()
{
    Game_Clock_Pub_Sub_Service* service = (Game_Clock_Pub_Sub_Service*)malloc(
        sizeof(Game_Clock_Pub_Sub_Service)
    );

    // Initialize all subscriber callbacks to empty function
    for (int i = 0; i < ANIMATION_CLOCK_COUNT; i++) {
        service->subscriber_callbacks[i] = game_clock_pub_sub_nop;
    }

    return service;
}

void register_pub_sub_subscriber(
    Game_Clock_Pub_Sub_Service* service,
    clock_subscriber_event_cb subscriber_callback, 
    Animation_Clock_Index animation_clock
)
{
    service->subscriber_callbacks[animation_clock] = subscriber_callback;
}

void register_pub_sub_tick_event(Game_Clock_Pub_Sub_Service* service, Tick_Event* tick_event)
{
    service->subscriber_callbacks[tick_event->clock_index](tick_event);
}

void free_pub_sub_service(Game_Clock_Pub_Sub_Service* service)
{
    free(service);
}
