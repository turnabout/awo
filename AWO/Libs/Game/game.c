#include "Game/_game.h"

Game* EMX create_game(int window_width, int window_height)
{
    Game* game = malloc(sizeof(Game));
    
    game->state = Game_Unusable;
    game->mode = No_Game_Mode;
    game->controller = NULL;

    game->window = create_game_window(window_width, window_height);
    game->data = create_game_data();

    // Set input handling modules
    // init_keyboard_module(game->window);
    // game->mouse_state = init_mouse_module(game->window);

    // Check that all essential modules were initialized properly
    if (game->data == NULL || game->window == NULL) {
        printe("Error initializing game modules");
        return game;
    }

    game->state = Game_Initialized;
    return game;
}

Game_State EMX get_game_state(Game* game)
{
    return game->state;
}

Game_Mode EMX get_game_mode(Game* game)
{
    return game->mode;
}

Game_Data* EMX get_game_data(Game* game)
{
    return game->data;
}

void EMX update_game_dimensions(Game* game, int width, int height)
{

    update_game_window_dimensions(game->window, width, height);

    // Send updated window dimensions to game controller
    if (game->controller != NULL) {
        // TODO
    }
}

void EMX free_game(Game* game)
{
    if (game == NULL) {
        return;
    }

    free_game_window(game->window);
    free_game_data(game->data);
    free(game);
}