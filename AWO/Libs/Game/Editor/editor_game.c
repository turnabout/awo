#include <stdlib.h>

#include "Game/Editor/_editor_game.h"

Game* create_editor_game(Game_Data* game_data, Game_Window* game_window)
{
    Editor_Game* game = malloc(sizeof(Editor_Game));

    if (game == NULL) {
        return NULL;
    }

    game->data = game_data;
    game->palette = 0;
    // game->stage_renderer = NULL;
    // game->extras_renderer = NULL;

    game->stage = generate_filled_stage(Plain, Default, 25, 25);

    // Set modules
    int* window_width, * window_height;
    get_game_window_dimensions_ptrs(game_window, &window_width, &window_height);

    game->camera = create_game_camera(
        window_width, 
        window_height, 
        game->stage->width, 
        game->stage->height
    );

    // game->stage_renderer = create_stage_renderer(game->stage, game_data);
    // game->extras_renderer = create_extras_renderer(game_data->sprite_sheet);
    // game->clock = create_clock(game_data->clock);

    // Update renderers' matrices
    // mat4 initial_projection;
    // create_projection_matrix(*window_width, *window_height, initial_projection);
    // update_stage_renderer_projection(game->stage_renderer, initial_projection);
    // update_extras_renderer_projection(game->extras_renderer, initial_projection);

    return (Game*)game;
}

void free_editor_game(Game* game)
{
    if (game == NULL) {
        return;
    }

    Editor_Game* editor_game = (Editor_Game*)game;

    free_stage(editor_game->stage);
    free_game_camera(editor_game->camera);
    // free_game_clock(editor_game->clock);
    // free_stage_renderer(editor_game->stage_renderer);
    // free_extras_renderer(editor_game->extras_renderer);

    free(editor_game);
}
