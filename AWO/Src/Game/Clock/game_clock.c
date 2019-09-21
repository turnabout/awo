#include <stdio.h>
#include <SDL.h>
#include "game_clock.h"
#include "conf.h"

#pragma warning( disable : 6011 )

struct Game_Clock {
    Uint8* current_tick;   // Current tick the game clock is on
    Uint32 accum_ms;       // Accumulated milliseconds

    Uint32 last_game_tick; // Result of SDL_GetTicks() last time the game clock was updated
};

Game_Clock* GC_create(void)
{
    Game_Clock* gc = (Game_Clock*)malloc(sizeof(Game_Clock));

    gc->current_tick = malloc(sizeof(Uint8));
    *(gc->current_tick) = 0;

    gc->accum_ms = 0;
    gc->last_game_tick = SDL_GetTicks();

    return gc;
}

void GC_update(Game_Clock* gc)
{
    // Get how many milliseconds passed since last update
    Uint32 current_tick= SDL_GetTicks();
    Uint32 delta = current_tick - gc->last_game_tick;

    gc->last_game_tick = current_tick;

    // Threshold reached, advance the current tick
    // Add to MS accumulation, advance current tick if threshold reached
    if ((gc->accum_ms += delta) > GAME_CLOCK_MAX_ACCUM_MS) {
        gc->accum_ms = 0;
        (*gc->current_tick)++;

        printf("Tick: %d\n", *(gc->current_tick));
    }
}

void GC_free(Game_Clock* gc)
{
    free(gc);
}
