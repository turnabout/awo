#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>

#include "conf.h"
#include "game.h"

#include "Visuals/data_init.h"

int init_game(Game* game)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_FLAGS) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return ERR;
    }

    // Initialize window
    game->win = SDL_CreateWindow(
        GAME_TITLE,              // Window title
        SDL_WINDOWPOS_CENTERED,  // Initial x pos
        SDL_WINDOWPOS_CENTERED,  // Initial y pos
        SCREEN_WIDTH,            // Width
        SCREEN_HEIGHT,           // Height
        SDL_WINDOW_FLAGS         // Flags
    );

    if (game->win == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return ERR;
    }

    // Initialize renderer
    game->rend = SDL_CreateRenderer(
        game->win, // Window where rendering is displayed
        -1,        // Index of rendering driver to initialize
        REND_INIT_FLAGS
    );

    if (game->rend == NULL) {
        printf("Could not create renderer: %s\n", SDL_GetError());
        return ERR;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
    SDL_RenderSetLogicalSize(game->rend, X1_SCREEN_WIDTH, X1_SCREEN_HEIGHT);

    // Initialize sprite sheet surface
    SDL_Surface* surface = IMG_Load(SPRITE_SHEET_PATH);

    if (surface == NULL) {
        printf("Error loading sprite sheet surface: %s\n", IMG_GetError());
        return ERR;
    }

    SDL_Surface* formatted_surface = SDL_ConvertSurfaceFormat(
        surface, 
        SDL_PIXELFORMAT_RGBA8888, 
        0
    );

    game->ss = SDL_CreateTextureFromSurface(game->rend, formatted_surface);

    SDL_FreeSurface(surface);
    SDL_FreeSurface(formatted_surface);

    if (game->ss == NULL) {
        printf("Error creating sprite sheet texture: %s\n", IMG_GetError());
        return ERR;
    }

    // Load & initialize the visuals data structure
    init_visuals_data_structure();

    return OK;
}

void exit_game(Game* game)
{
    if (game->win != NULL) {
        SDL_DestroyWindow(game->win);
    }

    if (game->rend != NULL) {
        SDL_DestroyRenderer(game->rend);
    }

    if (game->ss != NULL) {
        SDL_DestroyTexture(game->ss);
    }

    SDL_Quit();
}
