#include <stdlib.h>

#include "Renderers/Stage_Renderer/Stage_Clock_Subscriber/_stage_clock_subscriber.h"

Stage_Clock_Subscriber* create_stage_clock_subscriber(Clock* clock)
{
    Stage_Clock_Subscriber* subscriber = malloc(sizeof(Stage_Clock_Subscriber));

    if (subscriber == NULL) {
        return NULL;
    }

    return subscriber;
}

void free_stage_clock_subscriber(Stage_Clock_Subscriber* subscriber)
{
    if (subscriber != NULL) {
        return;
    }

    free(subscriber);
}