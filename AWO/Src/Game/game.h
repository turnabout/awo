#pragma once
#include <SDL.h>
#include "Visuals/visuals_data.h"

/**
 * \brief Holds components required to run the game.
 */
typedef struct Game
{
    SDL_Window*   win;
    SDL_Renderer* rend;
    SDL_Surface*  surface;
    SDL_Texture*  ss;
    Units_Data*   ud;
    // Tiles_Data*   td;
} Game;

/**
 *  \brief Initializes the game and populates the game instance pointed at by `game`.
 *
 *  \param game Pointer to the game instance.
 *
 *  \return Returns ERR if an error occurred, or OK.
 */
int init_game(Game* game);

/**
 *  \brief Exits the game and cleans up resources.
 *
 *  \param game Pointer to the game instance.
 */
void exit_game(Game* game);

/**
 *  \brief Runs the main game loop continuously.
 *
 *  \param game Pointer to the game instance.
 */
void run_game(Game* game);
