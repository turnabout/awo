#include <stdlib.h>

#include "Game/_game.h"

Game* create_game(int window_width, int window_height)
{
    Game* game = malloc(sizeof(Game));

    // Set default window dimension values if none given
    game->window_width = (window_width) ? window_width : DEFAULT_WINDOW_WIDTH;
    game->window_height = (window_height) ? window_height : DEFAULT_WINDOW_HEIGHT;

    // Initialize base GL game components (GLFW/GLAD/)
    if (!init_GL(game)) {
        free_game(game);
        return NULL;
    }

    // Initialize game data
    game->data = create_game_data();

    // Initialize input handling modules
    init_keyboard_module(game->window);
    game->mouse_state = init_mouse_module(game->window);

    // Initialize the game tile cursor module
    game->cursor = create_game_cursor(game->data->UI_data);

    // Check all modules were initialized properly
    if (
        game->data == NULL || 
        game->mouse_state == NULL || 
        game->cursor == NULL
    ) {
        free_game(game);
        return NULL;
    }
    
    // Initialize all other game struct members
    game->board = NULL;
    game->camera = NULL;
    game->clock = NULL;
    game->editor = NULL;
    game->renderer = NULL;
    game->palette_texture = 0;

    return game;
}