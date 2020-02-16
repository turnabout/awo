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
    // game->stage = generate_filled_stage(Sea, Middle, 25, 25);
    game->stage = generate_custom_stage();

    // Set the sprite sheet texture
    game->sprite_sheet = get_sprite_sheet_GL_texture(game_data->sprite_sheet);

    // Set the palette texture
    game->palette = create_game_palette_texture(
        game_data->palette,
        Clear,
        (Army_Type[]){ OS, BM, GE, YC }
    );

    // Set modules
    int* window_width, * window_height;
    get_game_window_dimensions_ptrs(game_window, &window_width, &window_height);

    game->camera = create_game_camera(
        window_width, 
        window_height, 
        game->stage->width, 
        game->stage->height
    );

    game->clock = create_clock(game_data->clock);

    game->stage_renderer = create_stage_renderer(
        game->stage,
        game->palette,
        game->sprite_sheet,
        game->data
    );

    game->extras_renderer = create_extras_renderer(game->sprite_sheet);

    // Initially call game's dimensions update function
    game->update_dimensions(game, *window_width, *window_height);

    // Initially set the view matrices for renderers
    update_extras_renderer_view(game->extras_renderer, 100, 100, 16.0f);
    update_stage_renderer_view(game->stage_renderer, 0, 0, 16.0f);

    // Inputs
    game->keyboard_state = create_keyboard_state();
    game->mouse_state = create_mouse_state();
    create_keyboard_handler(game_window);
    create_mouse_handler(game_window);

    return (Game*)game;
}

void free_editor_game(Game* game)
{
    if (game == NULL) {
        return;
    }

    Editor_Game* editor_game = (Editor_Game*)game;

    delete_texture(editor_game->sprite_sheet);
    delete_texture(editor_game->palette);

    free_stage(editor_game->stage);
    free_game_camera(editor_game->camera);
    free_clock(editor_game->clock);
    free_extras_renderer(editor_game->extras_renderer);
    free_stage_renderer(editor_game->stage_renderer);

    free_keyboard_state(editor_game->keyboard_state);
    free_mouse_state(editor_game->mouse_state);
    free_keyboard_handler();
    free_mouse_handler();

    free(editor_game);
}
