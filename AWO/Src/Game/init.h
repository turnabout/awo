/**
 * Game initialization/exiting functions.
 */

/**
 *  \brief Initializes the game and sets starting values (window, renderer, 
 *         sprite sheet) on the given game instance.
 *
 *  \param game Pointer to the game instance.
 *
 *  \return Returns ERR if an error occurred, or OK.
 *
 *  \sa init_game()
 */
int init_game(Game* game);

/**
 *  \brief Exits the game and cleans up resources.
 *
 *  \param game Pointer to the game instance.
 *
 *  \sa exit_game()
 */
void exit_game(Game* game);
