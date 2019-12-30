#include "Game/_game.h"

Bool prepare_game(Game* game, Stage* stage, CO_Type player_COs[MAX_PLAYER_COUNT])
{
    if (stage == NULL) {
        return FALSE;
    }

    // Prepare components used for rendering the game
    game->palette = create_game_palette_texture(
        game->data->raw_palette, 
        WEATHER_DEFAULT, 
        stage->player_armies
    );

    // Renderer
    game->renderer = create_game_renderer(
        stage->width,
        stage->height,
        game->palette,
        game->data->tiles,
        game->window_width,
        game->window_height
    );

    if (game->renderer == NULL) {
        unprepare_game(game);
        return FALSE;
    }

    // Clock
    game->clock = create_game_clock(game->data->clock, game->renderer, &game->palette);

    // Camera
    game->camera = create_game_camera(
        game->renderer, 
        &game->window_width, 
        &game->window_height, 
        stage
    );

    if (game->camera == NULL) {
        unprepare_game(game);
        return FALSE;
    }

    // Board
    game->board = create_game_board(
        game->clock, 
        game->renderer,
        stage, 
        player_COs,
        game->data->tiles, 
        game->data->raw_palette,
        game->palette
    );

    if (game->board == NULL) {
        unprepare_game(game);
        return FALSE;
    }

    game->state = Game_Prepared;
    return TRUE;
}
