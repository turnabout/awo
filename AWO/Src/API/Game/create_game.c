#include <stdlib.h>

#include "emx.h"
#include "Game/_game.h"

Game* EMX create_game(int window_width, int window_height)
{
    Game* game = malloc(sizeof(Game));

    game->state = Game_Unusable;

    // Initialize the message service, so messages can be logged
    start_message_service();
    
    // Set all struct members not to be initialized in this step
    game->board = NULL;
    game->camera = NULL;
    game->clock = NULL;
    game->editor = NULL;
    game->renderer = NULL;
    game->palette = 0;

    // Set default window dimension values if none given
    game->window_width = (window_width) ? window_width : DEFAULT_WINDOW_WIDTH;
    game->window_height = (window_height) ? window_height : DEFAULT_WINDOW_HEIGHT;

    // Initialize base GL game components (GLFW/GLAD)
    if (!init_GL(game)) {
        printe("Error initializing GL");
        return game;
    }

    // Initialize game data
    game->data = create_game_data();

    // Initialize input handling modules
    init_keyboard_module(game->window);
    game->mouse_state = init_mouse_module(game->window);

    // Initialize the game tile cursor module
    game->cursor = create_game_cursor(game->data->UI);

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