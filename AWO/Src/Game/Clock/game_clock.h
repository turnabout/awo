#pragma once

// Main game clock used for updating and keeping animations synchronized.
typedef struct Game_Clock Game_Clock;

// Create the game clock, along with its animation clocks using the given data JSON
Game_Clock* GC_create(const cJSON* json);

// Update the game clock's current tick value
void GC_update(Game_Clock* gc);

// Free the game clock's allocated memory
void GC_free(Game_Clock* clock);