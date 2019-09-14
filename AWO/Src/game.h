#pragma once
#include <SDL.h>

/**
 * \brief Represents the game and holds the SDL components required to run it.
 */
typedef struct Game
{
    SDL_Window* win;
    SDL_Renderer* rend;
    SDL_Surface* surface;
    SDL_Texture* ss;
} Game;
