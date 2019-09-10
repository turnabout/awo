/**
 * Game initialization/exiting functions.
 */

/**
 *  \brief Initializes the game and sets starting values (window, renderer, 
 *         sprite sheet).
 *
 *  \param window Pointer to the window pointer which will store the resulting
 *                window.
 *
 *  \param renderer Pointer to the renderer pointer which will store the 
 *                  resulting renderer.
 *
 *  \param ss       Pointer to the surface pointer which will store the 
 *                  resulting sprite sheet surface.
 *
 *  \return Returns ERR if an error occurred, or OK.
 *
 *  \sa init_game()
 */
int init_game(SDL_Window** window, SDL_Renderer** renderer, SDL_Surface** ss);

/**
 *  \brief Exits the game and cleans up resources.
 *
 *  \param window Pointer to the window pointer to destroy.
 *
 *  \param renderer Pointer to the renderer pointer to destroy.
 *
 *  \param renderer Pointer to the sprite sheet surface pointer to destroy.
 *
 *  \sa exit_game()
 */
void exit_game(SDL_Window** window, SDL_Renderer** renderer, SDL_Surface** ss);
