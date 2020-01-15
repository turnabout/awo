#include "Game/_game.h"

Game* EMX create_game(int window_width, int window_height)
{
    Game* game = malloc(sizeof(Game));
    
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
    // init_keyboard_module(game->window);
    // game->mouse_state = init_mouse_module(game->window);

    // Check all modules were initialized properly
    if (game->data == NULL) {
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

void EMX update_game_window_dimensions(Game* game, int width, int height)
{

    glfwSetWindowSize(game->window, width, height);
    glViewport(0, 0, width, height);

    game->window_width = width;
    game->window_height = height;

    // Send updated window dimensions to game controller
    if (game->controller != NULL) {
        // TODO
    }
}

void EMX free_game(Game* game)
{
    glfwTerminate();

    if (game == NULL) {
        return;
    }

    // Ensure game is "unprepared"
    unprepare_game(game);

    free_game_data(game->data);
    free(game);
}