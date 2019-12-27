#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Game/Clock/Tick_Event/tick_event.h"

typedef struct Game_Clock_Property_Lights_Subscriber Game_Clock_Property_Lights_Subscriber; 

Game_Clock_Property_Lights_Subscriber* create_game_clock_property_lights_subscriber(
    GLuint* game_palette
);

void process_property_light_tick_event(Tick_Event* tick_event, void* subscriber_module);

void free_game_clock_property_lights_subscriber(Game_Clock_Property_Lights_Subscriber* subscriber);
