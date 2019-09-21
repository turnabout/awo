#pragma once
#include <SDL.h>

#include "Visuals/visuals_data.h"
#include "Clock/game_clock.h"

// Holds components required to run the game.
typedef struct Game
{
    SDL_Window*   win;
    SDL_Renderer* rend;
    SDL_Surface*  surface;
    SDL_Texture*  ss;
    Units_Data*   ud;
    Tiles_Data*   td;
    Game_Clock*   clock;
} Game;

// Initializes the game and populates the game instance pointed at by `game`.
// Returns ERR if an error occured, or OK.
int init_game(Game* game);

// Exits the game and cleans up resources.
void exit_game(Game* game);

// Runs the main game loop continuously.
void run_game(Game* game);
