#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "../conf.h"

int init_game(SDL_Window** window, SDL_Renderer** renderer, SDL_Surface** ss)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_FLAGS) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return ERR;
    }

    // Initialize window
    *window = SDL_CreateWindow(
        GAME_TITLE,              // Window title
        SDL_WINDOWPOS_CENTERED,  // Initial x pos
        SDL_WINDOWPOS_CENTERED,  // Initial y pos
        SCREEN_WIDTH,            // Width
        SCREEN_HEIGHT,           // Height
        SDL_WINDOW_FLAGS         // Flags
    );

    if (*window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return ERR;
    }

    // Initialize renderer
    *renderer = SDL_CreateRenderer(
        *window, // Window where rendering is displayed
        -1,      // Index of rendering driver to initialize
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC // Flags
    );

    if (*renderer == NULL) {
        printf("Could not create renderer: %s\n", SDL_GetError());
        return ERR;
    }

    // Initialize sprite sheet
    *ss = IMG_Load("Resources/spritesheet.png");

    if (*ss == NULL) {
        printf("Error loading sprite sheet surface: %s\n", IMG_GetError());
        return ERR;
    }

    return OK;
}

void exit_game(SDL_Window** window, SDL_Renderer** renderer, SDL_Surface** ss)
{
    if (*window != NULL) {
        SDL_DestroyWindow(*window);
    }

    if (*renderer != NULL) {
        SDL_DestroyRenderer(*renderer);
    }

    if (*ss != NULL) {
        SDL_FreeSurface(*ss);
    }

    SDL_Quit();
}
