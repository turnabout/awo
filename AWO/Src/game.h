#pragma once
#include <SDL.h>
#include "cJSON/cJSON.h"

/**
 * \brief Represents the game and holds the SDL components required to run it.
 */
typedef struct Game
{
    SDL_Window* win;
    SDL_Renderer* rend;
    SDL_Texture* ss;
} Game;
