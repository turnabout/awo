#include <stdlib.h>

#include "Game/Data/Palette/game_palette.h"
#include "Game/Clock/Subscribers/Property_Lights/_property_lights_subscriber.h"
#include "Game/Clock/Pub_Sub/pub_sub.h"

struct Game_Clock_Property_Lights_Subscriber {

    // Pointer to the game palette's object id.
    GLuint* game_palette;

};

Game_Clock_Property_Lights_Subscriber* create_game_clock_property_lights_subscriber(
    GLuint* game_palette
)
{
    Game_Clock_Property_Lights_Subscriber* subscriber = malloc(
        sizeof(Game_Clock_Property_Lights_Subscriber)
    );

    subscriber->game_palette = game_palette;

    return subscriber;
}

void process_property_light_tick_event(Tick_Event* tick_event, void* subscriber_module)
{
    update_game_palette_property_lights(
        *((Game_Clock_Property_Lights_Subscriber*)subscriber_module)->game_palette,
        tick_event->value
    );
}

void free_game_clock_property_lights_subscriber(Game_Clock_Property_Lights_Subscriber* subscriber)
{
    if (subscriber != NULL) {
        free(subscriber);
    }
}