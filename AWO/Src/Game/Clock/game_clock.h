#pragma once

// Main game clock used for updating and keeping animations synchronized.
// Ticks constantly from 0 to 255.
typedef struct Game_Clock Game_Clock;

// Create the game clock
Game_Clock* GC_create(void);

// Update the game clock's current tick value
void GC_update(Game_Clock* gc);

// Free the game clock's allocated memory
void GC_free(Game_Clock* clock);