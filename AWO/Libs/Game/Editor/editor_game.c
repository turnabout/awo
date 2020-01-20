#include <stdlib.h>

#include "Game/Editor/_editor_game.h"

Game* EMX create_editor_game(Game_Data* game_data, Game_Window* game_window)
{
    Editor_Game* game = malloc(sizeof(Editor_Game));

    if (game == NULL) {
        return NULL;
    }

    game->update = update_editor_game;
    game->render = render_editor_game;
    game->update_dimensions = update_editor_game_dimensions;
    game->data = game_data;
    game->palette = 0; // TODO
    // game->stage_renderer = NULL;

    game->stage = generate_filled_stage(Plain, Default, 25, 25);

    // Set the sprite sheet texture
    game->sprite_sheet = get_sprite_sheet_GL_texture(game_data->sprite_sheet);

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
    game->extras_renderer = create_extras_renderer(game->sprite_sheet);
    // game->clock = create_clock(game_data->clock);

    // Initially call game's dimensions update function
    game->update_dimensions(game, *window_width, *window_height);

    update_extras_renderer_view(game->extras_renderer, 100, 100, 16.0f);

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
