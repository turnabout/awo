#include <stdlib.h>

#include "emx.h"
#include "Game/_game.h"

Game* EMX create_game(int window_width, int window_height)
{
    Game* game = malloc(sizeof(Game));

    // Initialize the message service, so messages can be logged
    start_message_service();
    
    game->state = Game_Unusable;
    game->mode = No_Game_Mode;
    game->controller = NULL;

    if (!init_game_rendering(
        game,
        (window_width) ? window_width : DEFAULT_WINDOW_WIDTH,
        (window_height) ? window_height : DEFAULT_WINDOW_HEIGHT
    )) {
        return game;
    }

    game->data = create_game_data();

    // Set input handling modules
    init_keyboard_module(game->window);
    game->mouse_state = init_mouse_module(game->window);

    // Check all modules were initialized properly
    if (
        game->data == NULL || 
        game->mouse_state == NULL || 
        game->cursor == NULL
    ) {
        printe("Error initializing game modules");
        return game;
    }

    game->state = Game_Initialized;
    return game;
}